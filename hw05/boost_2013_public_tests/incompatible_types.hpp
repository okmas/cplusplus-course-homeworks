#include <inttypes.h>

struct incompatible_1 {
	explicit incompatible_1(unsigned int value):m_value(value){;}
	unsigned int m_value;
};

struct incompatible_2 {
	explicit incompatible_2(unsigned int value):m_value(value){;}
	unsigned int m_value;
};

struct incompatible_3 {
	explicit incompatible_3(unsigned int value):m_value(value){;}
	unsigned int m_value;
};

struct incompatible_4 {
	explicit incompatible_4(unsigned int value):m_value(value){;}
	unsigned int m_value;
};

struct incompatible_5 {
	explicit incompatible_5(unsigned int value):m_value(value){;}
	unsigned int m_value;
};

struct incompatible_6 {
	explicit incompatible_6(unsigned int value):m_value(value){;}
	unsigned int m_value;
};
