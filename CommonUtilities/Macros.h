#pragma once

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SAFE_DELETE(aPointer) delete[] (aPointer); (aPointer) = nullptr;

#define FOR_EACH_NEED_INDEX(i, vector) for(i = 0; i < static_cast<int>(vector.size()); i++)

#define FOR_EACH(vector) for(unsigned int i = 0; i < vector.size(); i++)
#define FOR_EACH_GA(growingarray) for(unsigned int i = 0; i < growingarray.Size(); i++)

#define CYCLIC_ERASE(vector, index) vector[index] = vector[vector.size() - 1]; vector.pop_back();

#define UNLESS(x) if ((x) == false)
#define UNTIL(x) while ((x) == false)
#define GET_PERCENTAGE(numerator, denumerator) ((static_cast<long double>((numerator)) / static_cast<long double>((denumerator))) * 100.0)

#define PI 3.14159265f

#define CU_MAX(_aFirstValue,_aSecondValue)((_aFirstValue>_aSecondValue) ? _aFirstValue : _aSecondValue)

#define CU_MIN(_aFirstValue,_aSecondValue)((_aFirstValue<_aSecondValue) ? _aFirstValue : _aSecondValue)

#define CU_SAFE_DELETE(_aPointer)delete (_aPointer);(_aPointer) = nullptr;

#define CU_SAFE_DELETE_ARRAY(_aPointer)delete[] (_aPointer);(_aPointer) = nullptr;

#define CU_FOR_EACH_FROM_INDEX(_aIndex,_aVector)for(unsigned int _i=_aIndex; _i < _aVector.size(); ++_i)

#define CU_FOR_EACH(aVector)for(unsigned int _i = 0; _i < aVector.size(); ++_i)

#define CU_CYCLIC_ERASE(_aIndex,_aVector)_aVector[(_aIndex)] = _aVector[_aVector.size() - 1];_aVector.pop_back();

#define CU_REPEAT(_aTimes) for(int _i=0;_i<_aTimes;++_i)

#define CU_IS_EVEN(_aNumber) ((_aNumber)%2==0)

#define CU_RANGE(_aValue,_aLow,_aHigh) ((_aValue)>(_aHigh) ? (_aHigh) : ((_aValue)<(_aLow) ? (_aLow) : (_aValue)))

#define CU_ROUND_TO_INT(_aValue) static_cast<int>((_aValue)+0.5f)

#define CU_DEGREE_TO_RADAINS(_aValue) ((PI/180)*(_aValue))

#define CU_RAND(_aStartValue, _aEndValue) std::rand()%(((_aEndValue)+1)-(_aStartValue)) + (_aStartValue)