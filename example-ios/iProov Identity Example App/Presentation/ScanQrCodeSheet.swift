//
//  ScanQrCodeSheet.swift
//  iProov Identity Sample App
//
//  Created by Josh Everett on 27/01/2025.
//

import Foundation
import SwiftUI
import AVFoundation
import Vision

struct ScanQrCodeSheet: View {
    let dismiss: () -> Void
    let onQrScanned: (_ qr: String) -> Void

    var body: some View {
        ScannerView(onQrScanned: onQrScanned)
            .ignoresSafeArea()
    }
}

struct ScannerView: UIViewControllerRepresentable {
    let onQrScanned: (_ qr: String) -> Void

    func makeUIViewController(context: Context) -> QRScannerViewController {
        let controller = QRScannerViewController()
        controller.onQrScanned = { payload in
            Task { @MainActor in
                AudioServicesPlaySystemSound(SystemSoundID(kSystemSoundID_Vibrate))
                onQrScanned(payload)
            }
        }
        return controller
    }

    func updateUIViewController(_ uiViewController: QRScannerViewController, context: Context) {}
}

/// UIViewController that manages the camera capture session lifecycle.
final class QRScannerViewController: UIViewController {
    var onQrScanned: ((String) -> Void)?

    private let captureSession = AVCaptureSession()
    private var previewLayer: AVCaptureVideoPreviewLayer?
    private let videoQueue = DispatchQueue(label: "com.iproov.identity.qrscanner")
    private var hasScanned = false

    override func viewDidLoad() {
        super.viewDidLoad()
        setupCamera()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        hasScanned = false
        startScanning()
    }

    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        stopScanning()
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        previewLayer?.frame = view.bounds
    }

    private func setupCamera() {
        guard let videoCaptureDevice = AVCaptureDevice.default(for: .video),
              let videoInput = try? AVCaptureDeviceInput(device: videoCaptureDevice),
              captureSession.canAddInput(videoInput) else {
            return
        }

        captureSession.addInput(videoInput)

        let videoOutput = AVCaptureVideoDataOutput()
        if captureSession.canAddOutput(videoOutput) {
            videoOutput.setSampleBufferDelegate(self, queue: videoQueue)
            captureSession.addOutput(videoOutput)
        }

        let preview = AVCaptureVideoPreviewLayer(session: captureSession)
        preview.videoGravity = .resizeAspectFill
        preview.frame = view.bounds
        view.layer.addSublayer(preview)
        previewLayer = preview
    }

    private func startScanning() {
        guard !captureSession.isRunning else { return }
        videoQueue.async { [weak self] in
            self?.captureSession.startRunning()
        }
    }

    private func stopScanning() {
        guard captureSession.isRunning else { return }
        videoQueue.async { [weak self] in
            self?.captureSession.stopRunning()
        }
    }
}

extension QRScannerViewController: AVCaptureVideoDataOutputSampleBufferDelegate {
    func captureOutput(_ output: AVCaptureOutput, didOutput sampleBuffer: CMSampleBuffer, from connection: AVCaptureConnection) {
        guard !hasScanned,
              let pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer) else {
            return
        }

        let request = VNDetectBarcodesRequest()
        let handler = VNImageRequestHandler(cvPixelBuffer: pixelBuffer, orientation: .up, options: [:])

        do {
            try handler.perform([request])
            if let payload = request.results?.first?.payloadStringValue {
                hasScanned = true
                captureSession.stopRunning()
                onQrScanned?(payload)
            }
        } catch {
            print("Barcode detection failed: \(error)")
        }
    }
}
