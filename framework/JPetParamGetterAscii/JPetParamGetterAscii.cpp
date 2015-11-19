/**
  *  @copyright Copyright (c) 2014, Wojciech Krzemien
  *  @file JPetParamGetterAscii.cpp
  *  @author Wojciech Krzemien, wojciech.krzemien@if.uj.edu.pl
  */

#include "./JPetParamGetterAscii.h"
#include "../JPetParamBank/JPetParamBank.h"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>

JPetParamGetterAscii::JPetParamGetterAscii()
{
  /**/
}

JPetParamBank* JPetParamGetterAscii::generateParamBank(const char* filename, int runNumber)
{
  auto paramBank = loadFileContent(filename, runNumber);
  return paramBank;
}

/// assuming that file is in json format
//
JPetParamBank* JPetParamGetterAscii::loadFileContent(const char* filename, int runNumber)
{
  JPetParamBank* bank = 0;
  if (boost::filesystem::exists(filename)) {
    boost::property_tree::ptree dataFromFile;
    boost::property_tree::read_json(filename, dataFromFile);
    for ( auto it : dataFromFile) {
      std::cout << it.first << std::endl;
      //std::cout << it.second << std::endl;
      const auto &conf_data = it.second;
      auto bslotid1 = conf_data.get("bslot1.id", -1);
      auto bslotid2 = conf_data.get("bslot2.id", -1);

      auto bslotactive1 = conf_data.get("bslot1.active", false);
      auto bslotactive2 = conf_data.get("bslot2.active", false);

      auto bslotname1 = conf_data.get("bslot1.name", std::string(""));
      auto bslotname2 = conf_data.get("bslot2.name", std::string(""));

      auto bslottheta1 = conf_data.get("bslot1.theta", -1.f);
      auto bslottheta2 = conf_data.get("bslot2.theta", -1.f);

      auto bslotframe1 = conf_data.get("bslot1.frame", -1);
      auto bslotframe2 = conf_data.get("bslot2.frame", -1);


      auto pmid1 = conf_data.get("pm1.id", 0);
      auto pmid2 = conf_data.get("pm2.id", 0);
      auto pmid3 = conf_data.get("pm3.id", 0);
      auto pmid4 = conf_data.get("pm4.id", 0);

      auto scinid1 = conf_data.get("scin1.id", 0);
      auto scinid2 = conf_data.get("scin2.id", 0);

      // Create Parametric objects

      JPetBarrelSlot bslot1 (bslotid1, bslotactive1, bslotname1, bslottheta1, bslotframe1);
      JPetBarrelSlot bslot2 (bslotid2, bslotactive2, bslotname2, bslottheta2, bslotframe2);

      JPetPM pm1;
      JPetPM pm2;
      JPetPM pm3;
      JPetPM pm4;

      JPetScin scin1;
      JPetScin scin2;

      pm1.setID(pmid1);
      pm2.setID(pmid2);
      pm3.setID(pmid3);
      pm4.setID(pmid4);

      scin1.setID(scinid1);
      scin2.setID(scinid2);

      bank = new JPetParamBank();

      bank->addBarrelSlot(bslot1);
      bank->addBarrelSlot(bslot2);

      bank->addPM(pm1);
      bank->addPM(pm2);
      bank->addPM(pm3);
      bank->addPM(pm4);

      bank->addScintillator(scin1);
      bank->addScintillator(scin2);

      (bank->getPM(0)).setScin(bank->getScintillator(0));
      (bank->getPM(1)).setScin(bank->getScintillator(0));
      (bank->getPM(2)).setScin(bank->getScintillator(1));
      (bank->getPM(3)).setScin(bank->getScintillator(1));

      (bank->getPM(0)).setBarrelSlot(bank->getBarrelSlot(0));
      (bank->getPM(1)).setBarrelSlot(bank->getBarrelSlot(0));
      (bank->getPM(2)).setBarrelSlot(bank->getBarrelSlot(1));
      (bank->getPM(3)).setBarrelSlot(bank->getBarrelSlot(1));

      (bank->getScintillator(0)).setBarrelSlot(bank->getBarrelSlot(0));
      (bank->getScintillator(1)).setBarrelSlot(bank->getBarrelSlot(1));
    }
  } else {
    ERROR(std::string("Input file does not exist:") + filename);
  }
  return bank;
}
