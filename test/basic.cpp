#include <iostream>
#include <cstdio>
#include "fixed_point_number.h"

using namespace fixed_point_number;
using namespace std;

bool test1()
{
	char buffer_a[256], buffer_b[256], buffer_c[256];
	
	struct test_fixed_point_number {
		FXP_S32_31 a;
		FXP_S32_31 b;
		char op;
		FXP_S32_31 c;
	};
	const test_fixed_point_number test_data_table[] = {
		{ FXP_S32_31(2), FXP_S32_31 (3), '+', FXP_S32_31(5) },
		{ FXP_S32_31(2), FXP_S32_31 (3), '-', FXP_S32_31(-1) },
		{ FXP_S32_31(2), FXP_S32_31 (3), '*', FXP_S32_31(6) },
		{ FXP_S32_31(2), FXP_S32_31 (3), '/', FXP_S32_31(2,3) },
		{ FXP_S32_31(2), FXP_S32_31(-4), '+', FXP_S32_31(-2) },
		{ FXP_S32_31(2), FXP_S32_31(-4), '-', FXP_S32_31(6) },
		{ FXP_S32_31(3), FXP_S32_31(-4), '*', FXP_S32_31(-12) },
		{ FXP_S32_31(3), FXP_S32_31(-4), '/', FXP_S32_31(-3,4) },
		{ FXP_S32_31(-2), FXP_S32_31(4), '+', FXP_S32_31(2) },
		{ FXP_S32_31(-2), FXP_S32_31(4), '-', FXP_S32_31(-6) },
		{ FXP_S32_31(-3), FXP_S32_31(4), '*', FXP_S32_31(-12) },
		{ FXP_S32_31(-3), FXP_S32_31(4), '/', FXP_S32_31(-3,4) },
		{ FXP_S32_31(-2), FXP_S32_31(-4), '+', FXP_S32_31(-6) },
		{ FXP_S32_31(-2), FXP_S32_31(-4), '-', FXP_S32_31(2) },
		{ FXP_S32_31(-3), FXP_S32_31(-4), '*', FXP_S32_31(12) },
		{ FXP_S32_31(-3), FXP_S32_31(-4), '/', FXP_S32_31(3,4) },
		{ 1, 3, '/', FXP_S32_31(1,3) },
	};
		
	// check loop
	FXP_S32_31 a, b, c;
	bool judge;
	for (test_fixed_point_number test_data : test_data_table) {
		switch (test_data.op) {
		case '+':
		    c = test_data.a + test_data.b;
			judge = (test_data.a + test_data.b == test_data.c);
		    break;
		case '-':
		    c = test_data.a - test_data.b;
			judge = (test_data.a - test_data.b == test_data.c);
			break;
		case '*':
		    c = test_data.a * test_data.b;
			judge = (test_data.a * test_data.b == test_data.c);
			break;
		case '/':
		    c = test_data.a / test_data.b;
			judge = (test_data.a / test_data.b == test_data.c);
			break;
		}
		cout << "[" << (judge ? "OK" : "NG") << "] "
		     << test_data.a.toString(buffer_a, sizeof(buffer_a))
		     << " " << test_data.op << " "
			 << test_data.b.toString(buffer_b, sizeof(buffer_b))
			 << ": " <<  c.toString(buffer_c, sizeof(buffer_c)) << " == "
			 << test_data.c.toString(buffer_c, sizeof(buffer_c))
			 << endl;
	}
	return true;
}

int main(int _ac, char** _av)
{
    if (test1()) {
		return 0;
	} else {
		return -1;
	}
}
