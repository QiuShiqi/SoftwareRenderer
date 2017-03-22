#ifndef _StateMachine_H_
#define _StateMachine_H_

class StateMachine{
public:
	enum POINTERTYPE{
		PT_POSITION,
		PT_COLOR,
		PT_UV
	};

	enum DATATYPE{
		DT_BYTE,
		DT_FLOAT,
		DT_DOUBLE
	};

	struct DataElementInfo{
		int iSize;
		DATATYPE type;
		int iStride;
		const void* pData;
	};

private:
	DataElementInfo position;
	DataElementInfo color;
	DataElementInfo uv;

public:
	StateMachine();
	void vertexPointer(POINTERTYPE pointerType, int size, DATATYPE dataType, int stride, const void* data);
};

#endif