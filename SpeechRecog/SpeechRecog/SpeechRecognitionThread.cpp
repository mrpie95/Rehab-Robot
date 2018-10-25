//#include "SpeechRecognitionThread.h"

//using google::cloud::speech::v1::RecognitionConfig;
//using google::cloud::speech::v1::Speech;
//using google::cloud::speech::v1::StreamingRecognizeRequest;
//using google::cloud::speech::v1::StreamingRecognizeResponse;

//SpeechRecognitionThread::SpeechRecognitionThread() {

//}

//int SpeechRecognitionThread::start() {
//    // Create a Speech Stub connected to the speech service.
//    auto creds = grpc::GoogleDefaultCredentials();
//    auto channel = grpc::CreateChannel("speech.googleapis.com", creds);
//    std::unique_ptr<Speech::Stub> speech(Speech::NewStub(channel));

//    StreamingRecognizeRequest request;
//    auto* streaming_config = request.mutable_streaming_config();

//    // Begin a stream.
//    grpc::ClientContext context;
//    auto streamer = speech->StreamingRecognize(&context);
//    // Write the first request, containing the config only.
//    streaming_config->set_interim_results(true);
//    streamer->Write(request);
//    // The microphone thread writes the audio content.
//    std::thread microphone_thread(&MicrophoneThread, streamer.get());
//    // Read responses.
//    StreamingRecognizeResponse response;
//    while (streamer->Read(&response)) {  // Returns false when no more to read.
//        // Dump the transcript of all the results.
//        for (int r = 0; r < response.results_size(); ++r) {
//            auto result = response.results(r);
//            std::cout << "Result stability: " << result.stability() << std::endl;
//            for (int a = 0; a < result.alternatives_size(); ++a) {
//                auto alternative = result.alternatives(a);
//                std::cout << alternative.confidence() << "\t"
//                          << alternative.transcript() << std::endl;
//            }
//        }
//    }
//    grpc::Status status = streamer->Finish();
//    microphone_thread.join();
//    if (!status.ok()) {
//        // Report the RPC failure.
//        std::cerr << status.error_message() << std::endl;
//        return -1;
//    }
//    return 0;
//}

//void SpeechRecognitionThread::MicrophoneThread(grpc::ClientReaderWriterInterface<StreamingRecognizeRequest, StreamingRecognizeResponse>* streamer) {
//    StreamingRecognizeRequest request;
//    const size_t chunk_size = 64 * 1024;
//    std::vector<char> chunk(chunk_size);

//    std::ifstream file_stream("Clip 4.ogg");

//    while (true) {
//      // Read another chunk from the file.
//      std::streamsize bytes_read =
//          file_stream.rdbuf()->sgetn(&chunk[0], chunk.size());
//      // And write the chunk to the stream.
//      request.set_audio_content(&chunk[0], bytes_read);
//      std::cout << "Sending " << bytes_read / 1024 << "k bytes." << std::endl;
//      streamer->Write(request);
//      if (bytes_read < chunk.size()) {
//        // Done reading everything from the file, so done writing to the stream.
//        streamer->WritesDone();
//        break;
//      } else {
//        // Wait a second before writing the next chunk.
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//      }
//    }
//}
