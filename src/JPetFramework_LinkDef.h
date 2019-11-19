#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclasses;

#pragma link C++ function JPetWriter::Write(JPetChannel&);
#pragma link C++ function JPetWriter::Write(vector<JPetChannel>&);
#pragma link C++ function JPetWriter::Write(JPetPM&);
#pragma link C++ function JPetWriter::Write(vector<JPetPM>&);
#pragma link C++ function JPetWriter::Write(JPetScin&);
#pragma link C++ function JPetWriter::Write(vector<JPetScin>&);
#pragma link C++ function JPetWriter::Write(JPetSlot&);
#pragma link C++ function JPetWriter::Write(vector<JPetSlot>&);
#pragma link C++ function JPetWriter::Write(JPetLayer&);
#pragma link C++ function JPetWriter::Write(vector<JPetLayer>&);
#pragma link C++ function JPetWriter::Write(JPetSetup&);
#pragma link C++ function JPetWriter::Write(vector<JPetSetup>&);

#pragma link C++ function JPetWriter::Write(JPetTimeWindow&);
#pragma link C++ function JPetWriter::Write(vector<JPetTimeWindow>&);
#pragma link C++ function JPetWriter::Write(JPetSigCh&);
#pragma link C++ function JPetWriter::Write(vector<JPetSigCh>&);
#pragma link C++ function JPetWriter::Write(JPetRawSignal&);
#pragma link C++ function JPetWriter::Write(vector<JPetRawSignal>&);
#pragma link C++ function JPetWriter::Write(JPetRecoSignal&);
#pragma link C++ function JPetWriter::Write(vector<JPetRecoSignal>&);
#pragma link C++ function JPetWriter::Write(JPetMatrixSignal&);
#pragma link C++ function JPetWriter::Write(vector<JPetMatrixSignal>&);
#pragma link C++ function JPetWriter::Write(JPetPhysSignal&);
#pragma link C++ function JPetWriter::Write(vector<JPetPhysSignal>&);
#pragma link C++ function JPetWriter::Write(JPetHit&);
#pragma link C++ function JPetWriter::Write(vector<JPetHit>&);
#pragma link C++ function JPetWriter::Write(JPetLOR&);
#pragma link C++ function JPetWriter::Write(vector<JPetLOR>&);
#pragma link C++ function JPetWriter::Write(JPetEvent&);
#pragma link C++ function JPetWriter::Write(vector<JPetEvent>&);

#pragma link C++ class JPetParamBank+;
#pragma link C++ class JPetTreeHeader+;
#pragma link C++ class JPetStatistics+;

#pragma link C++ class JPetChannel+;
#pragma link C++ class JPetPM+;
#pragma link C++ class JPetScin+;
#pragma link C++ class JPetSlot+;
#pragma link C++ class JPetLayer+;
#pragma link C++ class JPetSetup+;

#pragma link C++ class JPetTimeWindow+;
#pragma link C++ class JPetSigCh+;
#pragma link C++ class JPetBaseSignal+;
#pragma link C++ class JPetRawSignal+;
#pragma link C++ class JPetRecoSignal+;
#pragma link C++ class JPetPhysSignal+;
#pragma link C++ class JPetMatrixSignal+;
#pragma link C++ class JPetHit+;
#pragma link C++ class JPetLOR+;
#pragma link C++ class JPetEvent+;

#pragma link C++ class JPetTimeWindowMC+;
#pragma link C++ class JPetMCHit+;
#pragma link C++ class JPetMCDecayTree+;
#pragma link C++ class JPetGeantScinHits+;
#pragma link C++ class JPetGeantDecayTree+;
#pragma link C++ class JPetGeantEventPack+;
#pragma link C++ class JPetGeantEventInformation+;

#pragma link C++ struct JPetTreeHeader::ProcessingStageInfo+;
#pragma link C++ struct shapePoint+;

#pragma link C++ enum JPetSlot::Type;
#pragma link C++ enum JPetPM::Side;
#pragma link C++ enum JPetBaseSignal::RecoFlag;
#pragma link C++ enum JPetSigCh::RecoFlag;
#pragma link C++ enum JPetSigCh::EdgeType;
#pragma link C++ enum JPetHits::RecoFlag;
#pragma link C++ enum JPetEvent::RecoFlag;

#endif
