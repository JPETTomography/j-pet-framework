#ifndef _JPET_PM_
#define _JPET_PM_

class JPetPM {
public:
	typedef enum Side {kLeft, kRight};
	int getID() const {return fID;}
	void setID(int id) { fID = id; } 
private:
	Side fSide;
	int fID;
	int fHVset;
	int fHVopt;
	float fHVgain[2];
};

#endif