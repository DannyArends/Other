/**
 * \file GAME/GAMEstructures.h
 * \brief Header file, for the GAME directory
 *
 * This class is used to share the objects within the GAME directory with the other directories<br>
 * Furthermore it defines structures used, and dependencies needed<br>
 * Copyright (c) 2010 Danny Arends
 *
 **/

#ifndef GAMESTRUCTURES_H_
  #define GAMESTRUCTURES_H_
  #include "includes.h"

  /**
   * \brief Enumerator of possible user states
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum userstates { UNDEFINED = 0, STARTUP = 1, LOGINUSERLOCAL = 2, CREATENEWUSER = 3, PLAYUSERLOCAL = 4, PLAYGODLOCAL = 5, LOGINUSERREMOTE= 6, PLAYUSERREMOTE = 7, LOGOUTREMOTE = 8, LOGOUTLOCAL = 9 };

  /**
   * \brief Enumerator of possible NPC states
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum npctypes    { LIMBONPC = 0, CREATURE = 1, MONSTER = 2, QUESTNPC = 3, MERCHANTNPC = 4, STORAGENPC = 5, MOVINGNPC = 6, PLAYERLIKE = 7 };

  /**
   * \brief Enumerator of wearable positions
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum weartypes   { UNWEARABLE = 0, FRONT = 1, BACK = 2, LEFT = 3, RIGHT = 4, TOP = 5, BOTTOM = 6 };

  /**
   * \brief Enumerator of user attributes
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum attributes { CELLSTRENGTH = 0, CELLWALL = 1, CELLSIZE = 2, CELLTOUGHNESS = 3, CELLPOWER = 4};

  /**
   * \brief Enumerator of user nexus
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum nexus {ABSORPTIONNEXUS = 0, PRODUCTIONNEXUS = 1};

  /**
   * \brief Enumerator of user skills
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  enum skills { OVERALL =0, ATTACK = 1, DEFENCE = 2, ABSORPTION = 3, PRODUCTION = 4};


  /**
   * \brief User levels defined using \ref skills enumeration
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class userlevels : public databaseobject{
    public:
      userlevels(uint nlevels=5) : databaseobject::databaseobject(){
        this->nlevels=nlevels;
        for(uint i=0;i<nlevels;i++){
          base.push_back(0);
          bonus.push_back(0);
          xp.push_back(0);
        }
        this->initdb();
      }
      string           getobjectname(){ return "userlevels"; }
      bool             load(void){
        vector<string> values = this->getrow(this->getobjectname(),this->getparent()->getid());
        if(values.size()==0) return false;
        this->setid(atoi(values[0].c_str()));
        for(uint i=0;i<nlevels;i++){
          base[i]=atoi(values[(3*i)+1].c_str());
          bonus[i]=atoi(values[(3*i)+2].c_str());
          xp[i]=atoi(values[(3*i)+3].c_str());
        }
        return true;
      }
      ~userlevels(){ }

    private:
      vector<uint> base;
      vector<uint> bonus;
      vector<uint> xp;
      uint nlevels;
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        for(uint i=0;i<nlevels;i++){
          structs.push_back("base" + uinttostring(i));
          structs.push_back("bonus" + uinttostring(i));
          structs.push_back("xp" + uinttostring(i));
        }
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        for(uint i=0;i<nlevels;i++){
          types.push_back("INTEGER");
          types.push_back("INTEGER");
          types.push_back("INTEGER");
        }
        return types;
      }
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getparent()->getid()));
        for(uint i=0;i<nlevels;i++){
          values.push_back(uinttostring(this->base[i]));
          values.push_back(uinttostring(this->bonus[i]));
          values.push_back(uinttostring(this->xp[i]));
        }
        return values;
      }
  };

  /**
   * \brief User attributes defined using \ref attributes enumeration
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class userattributes : public databaseobject{
    public:
      userattributes(uint nattributes=5) : databaseobject::databaseobject(){
        this->nattributes=nattributes;
        for(uint i=0;i<nattributes;i++){
          base.push_back(0);
          bonus.push_back(0);
        }
        this->initdb();
      }
      string           getobjectname(){ return "userattributes"; }
      bool             load(void){
        vector<string> values = this->getrow(this->getobjectname(),this->getparent()->getid());
        if(values.size()==0) return false;
        this->setid(atoi(values[0].c_str()));
        for(uint i=0;i<nattributes;i++){
          base[i]=atoi(values[(2*i)+1].c_str());
          bonus[i]=atoi(values[(2*i)+2].c_str());
        }
        return true;
      }
      ~userattributes(){ }

    private:
      vector<uint> base;
      vector<uint> bonus;
      uint nattributes;
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        for(uint i=0;i<nattributes;i++){
          structs.push_back("base" + uinttostring(i));
          structs.push_back("bonus" + uinttostring(i));
        }
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        for(uint i=0;i<nattributes;i++){
          types.push_back("INTEGER");
          types.push_back("INTEGER");
        }
        return types;
      }
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getparent()->getid()));
        for(uint i=0;i<nattributes;i++){
          values.push_back(uinttostring(this->base[i]));
          values.push_back(uinttostring(this->bonus[i]));
        }
        return values;
      }
  };

  /**
   * \brief User attributes defined using \ref nexus enumeration
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class usernexus : public databaseobject{
    public:
      usernexus(uint nnexus=2) : databaseobject::databaseobject(){
        this->nnexus=nnexus;
        for(uint i=0;i<nnexus;i++){
          nexus.push_back(0);
        }
        this->initdb();
      }
      string           getobjectname(){ return "usernexus"; }
      bool             load(void){
        vector<string> values = this->getrow(this->getobjectname(),this->getparent()->getid());
        if(values.size()==0) return false;
        this->setid(atoi(values[0].c_str()));
        for(uint i=0;i<nnexus;i++){
          nexus[i]=atoi(values[i+1].c_str());
        }
        return true;
      }
      ~usernexus(){ }

    private:
      vector<uint> nexus;
      uint nnexus;
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        for(uint i=0;i<nnexus;i++){
          structs.push_back("nexus" + uinttostring(i));
        }
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        for(uint i=0;i<nnexus;i++){
          types.push_back("INTEGER");
        }
        return types;
      }
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getparent()->getid()));
        for(uint i=0;i<nnexus;i++){
          values.push_back(uinttostring(this->nexus[i]));
        }
        return values;
      }
  };

  /**
   * \brief User looks defined using race and \ref RGBcolor
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class userlooks : public databaseobject{
    public:
      userlooks(uint race=0) : databaseobject::databaseobject(){
        this->race=race;
        for(uint i=0;i<3;i++){
          colors.push_back(WHITE);
        }
        this->initdb();
      }
      string           getobjectname(){ return "userlooks"; }
      bool             load(void){
        vector<string> values = this->getrow(this->getobjectname(),this->getparent()->getid());
        if(values.size()==0) return false;
        this->setid(atoi(values[0].c_str()));
        this->race = atoi(values[1].c_str());
        for(uint i=0;i<9;i++){
          colors[i]=(RGBcolor){atof(values[(3*i)+2].c_str()),atof(values[(3*i)+3].c_str()),atof(values[(3*i)+4].c_str()),1.0f};
        }
        return true;
      }
      ~userlooks(){ }

    private:
      vector<RGBcolor> colors;
      uint race;
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        for(uint i=0;i<3;i++){
            structs.push_back("color" + uinttostring(i) + "r");
            structs.push_back("color" + uinttostring(i) + "g");
            structs.push_back("color" + uinttostring(i) + "b");
        }
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        for(uint i=0;i<3;i++){
          types.push_back("REAL");
          types.push_back("REAL");
          types.push_back("REAL");
        }
        return types;
      }
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getparent()->getid()));
        for(uint i=0;i<3;i++){
          values.push_back(floattostring(this->colors[i].r));
          values.push_back(floattostring(this->colors[i].g));
          values.push_back(floattostring(this->colors[i].b));
        }
        return values;
      }
  };

  /**
   * \brief User gear set defined using items and full gear bonus
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class usergear : public databaseobject{
    public:
      usergear(uint nlevels=5) : databaseobject::databaseobject(){
        this->nlevels=nlevels;
        for(uint i=0;i<7;i++){
          wearid.push_back(0);
        }
        for(uint i=0;i<nlevels;i++){
          skillbonus.push_back(0);
          attributebonus.push_back(0);

        }
        this->initdb();
      }
      string           getobjectname(){ return "usergear"; }
      bool             load(void){
        vector<string> values = this->getrow(this->getobjectname(),this->getparent()->getid());
        if(values.size()==0) return false;
        this->setid(atoi(values[0].c_str()));
        for(uint i=0;i<7;i++){
          wearid[i]=atoi(values[i+1].c_str());
        }
        for(uint i=0;i<nlevels;i++){
          skillbonus[i] = atoi(values[(2*i)+8].c_str());
          attributebonus[i] = atoi(values[(2*i)+9].c_str());
        }
        return true;
      }
      ~usergear(){ }

    private:
      vector<uint> wearid;
      vector<uint> skillbonus;
      vector<uint> attributebonus;
      uint nlevels;
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        for(uint i=0;i<7;i++){
          structs.push_back("wornitemid" + uinttostring(i));
        }
        for(uint i=0;i<nlevels;i++){
          structs.push_back("skill" + uinttostring(i));
          structs.push_back("attribute" + uinttostring(i));
        }
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        for(uint i=0;i<7;i++){
          types.push_back("INTEGER");
        }
        for(uint i=0;i<nlevels;i++){
          types.push_back("INTEGER");
          types.push_back("INTEGER");
        }
        return types;
      }
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getparent()->getid()));
        for(uint i=0;i<7;i++){
          values.push_back(uinttostring(wearid[i]));
        }
        for(uint i=0;i<nlevels;i++){
          values.push_back(uinttostring(skillbonus[i]));
          values.push_back(uinttostring(attributebonus[i]));
        }
        return values;
      }
  };

  /**
   * \brief Item attribute structure
   *
   * This objects item attribute flags like: reagent, resource, consumable, combinable, unstabile, stackable
   *
   * TODO Description<br>
   * bugs: none found<br>
   */
  class itemattributes : public databaseobject{
    public:
      itemattributes(uint nattributes=7) : databaseobject::databaseobject(){
        this->nattributes=nattributes;
        this->cooldown=0;
        this->maxcooldown=0;
        this->wearable=0;
        for(uint i=0;i<nattributes;i++){
          attributes.push_back(false);
        }
        this->initdb();
      }
      string           getobjectname(){ return "itemattributes"; }
      bool             load(void){
        vector<string> values = this->getrow(this->getobjectname(),this->getparent()->getid());
        if(values.size()==0) return false;
        this->setid(atoi(values[0].c_str()));
        this->cooldown = atoi(values[1].c_str());
        this->maxcooldown = atoi(values[2].c_str());
        this->wearable = atoi(values[3].c_str());
        for(uint i=0;i<nattributes;i++){
          attributes[i]=atoi(values[i+4].c_str());
        }
        return true;
      }
      ~itemattributes(){ }

    private:
      uint cooldown;
      uint maxcooldown;
      uint wearable;
      vector<bool> attributes;
      uint nattributes;
      vector<string>   decomposestructs(){
        vector<string> structs;
        structs.push_back(getobjectname() + "id");
        structs.push_back("wearable");
        structs.push_back("cooldown");
        structs.push_back("maxcooldown");
        structs.push_back("reagent");
        structs.push_back("resource");
        structs.push_back("tool");
        structs.push_back("consumable");
        structs.push_back("combinable");
        structs.push_back("unstabile");
        structs.push_back("stackable");
        return structs;
      }
      vector<string>   decomposetypes(){
        vector<string> types;
        types.push_back("INTEGER PRIMARY KEY");
        types.push_back("INTEGER");
        types.push_back("INTEGER");
        types.push_back("INTEGER");
        for(uint i=0;i<nattributes;i++){
          types.push_back("INTEGER");
        }
        return types;
      }
      vector<string>   decomposevalues(){
        vector<string> values;
        values.push_back(uinttostring(this->getparent()->getid()));
        values.push_back(uinttostring(this->wearable));
        values.push_back(uinttostring(this->cooldown));
        values.push_back(uinttostring(this->maxcooldown));
        for(uint i=0;i<nattributes;i++){
          values.push_back(uinttostring((uint)attributes[i]));
        }
        return values;
      }
  };

#endif

