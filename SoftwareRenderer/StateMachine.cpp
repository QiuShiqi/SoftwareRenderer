#include "StateMachine.h"
#include <string.h>

StateMachine::StateMachine(){
	memset(&(this->position), 0, sizeof(this->position));
	memset(&(this->color), 0, sizeof(this->color));
	memset(&(this->uv), 0, sizeof(this->uv));
}

void StateMachine::vertexPointer(POINTERTYPE pointerType, int size, DATATYPE dataType, int stride, const void* data){
	DataElementInfo *p = nullptr;

	switch(pointerType){
	case PT_POSITION:
		p = &(this->position);
		break;
	case PT_COLOR:
		p = &(this->color);
		break;
	case PT_UV:
		p = &(this->uv);
		break;
	}

	p->iSize = size;
	p->type = dataType;
	p->iStride = stride;
	p->pData = data;

}