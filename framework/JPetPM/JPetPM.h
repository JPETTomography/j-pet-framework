#ifndef _JPET_PM_
#define _JPET_PM_

class JPetPM {
public:
	typedef enum Side {kLeft, kRight};
private:
	Side fSide;
	int fPM_id;
	int fPM_HVset;
	int fPM_HVopt;
	float fPM_HVgain[2];
};

#endif