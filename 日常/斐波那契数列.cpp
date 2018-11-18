int f(int i)
{
	if (i == 1)
		return 1;
	if (i == 2)
		return 1;

	int a = 1;
	int b = 1;
	int f = 0;
	for (int c = 3; c <= i; ++c)
	{
		f = a + b;
		a = b;
		b = f;
	}
	return f;
}