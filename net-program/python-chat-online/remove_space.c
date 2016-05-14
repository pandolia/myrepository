#include <stdio.h>

void FormatString(char str[],int len){

}

int main(int argc, char const *argv[])
{
	char strs[5][20] = {
		"  I am   a little boy   !   ",
		"fdkajf fdasfd",
		"fdsafdsaf",
		"fafsdf   fdsafds   fdsafds",
		"   fdsaf fdsafsd fdsafdsa ",
	};

	for (int i = 0; i < 5; ++i)
	{
		printf("%s\n", strs[i]);
	}
	return 0;
}