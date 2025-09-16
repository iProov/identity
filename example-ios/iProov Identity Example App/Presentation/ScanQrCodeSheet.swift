//
//  PresentationSheet.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 27/01/2025.
//

import Foundation
import SwiftUI
import identity
import AVFoundation
import Vision


struct ScanQrCodeSheet: View {

    let dismiss: () -> Void
    let onQrScanned: (_ qr: String) -> Void
        
    var body: some View {
        ScannerView(onQrScanned: onQrScanned)
    }
}

@MainActor
struct ScannerView: UIViewControllerRepresentable {

    let onQrScanned: (_ qr: String) -> Void
    
    let captureSession = AVCaptureSession()
    
    func makeUIViewController(context: Context) -> UIViewController {
        let viewController = UIViewController()
        
        guard let videoCaptureDevice = AVCaptureDevice.default(for: .video),
              let videoInput = try? AVCaptureDeviceInput(device: videoCaptureDevice),
              captureSession.canAddInput(videoInput) else { return viewController }
        
        captureSession.addInput(videoInput)
        
        let videoOutput = AVCaptureVideoDataOutput()
        
        if captureSession.canAddOutput(videoOutput) {
            videoOutput.setSampleBufferDelegate(context.coordinator, queue: DispatchQueue(label: "videoQueue"))
            captureSession.addOutput(videoOutput)
        }
        
        let previewLayer = AVCaptureVideoPreviewLayer(session: captureSession)
        previewLayer.frame = viewController.view.bounds
        previewLayer.videoGravity = .resizeAspectFill
        viewController.view.layer.addSublayer(previewLayer)
        
        captureSession.startRunning()
        
        return viewController
    }
    
    func updateUIViewController(_ uiViewController: UIViewController, context: Context) {}
    
    func makeCoordinator() -> Coordinator {
        Coordinator(self)
    }
    
    class Coordinator: NSObject, AVCaptureVideoDataOutputSampleBufferDelegate {
            var parent: ScannerView
            
            init(_ parent: ScannerView) {
                self.parent = parent
            }
            
            func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
                guard let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer) else { return }
                self.detectBarcode(in: pixelBuffer)
            }
            
            func detectBarcode(in pixelBuffer: CVPixelBuffer) {
                let request = VNDetectBarcodesRequest()
                let handler = VNImageRequestHandler(cvPixelBuffer: pixelBuffer, orientation: .up, options: [:])
                
                do {
                    try handler.perform([request])
                    if let results = request.results, let payload = results.first?.payloadStringValue {
                        Task {
                            AudioServicesPlaySystemSound(SystemSoundID(kSystemSoundID_Vibrate))
                            await self.parent.onQrScanned(payload)
                        }
                        // Optionally, stop scanning after first detection
                         self.parent.captureSession.stopRunning()
                    }
                } catch {
                    print("Barcode detection failed: \\(error)")
                }
            }
        }
}
