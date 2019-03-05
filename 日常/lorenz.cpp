#include "configparser.h"

//向量
struct vec
{
	double x;
	double y;
	double z;
};

vec operator*(vec &v, double &n)
{
	return { v.x * n , v.y * n , v.z * n};
}

vec operator+(vec &x, vec &y)
{
	return {x.x + y.x, x.y + y.y, x.z + y.z};
}

//洛伦兹场参数
double a = 11;
double b = 27;
double c = 2;

//洛伦兹场
vec velocity(vec &pos)
{
	vec velocity;
	
	velocity.x = a * (pos.y - pos.x);
	velocity.y = pos.x * (b - pos.z) - pos.y;
	velocity.z = pos.x * pos.y - c * pos.z;

	return velocity;
}

//时间微元
double dt = 0.001;

int main()
{
	//初始条件
	vec init_state = { 5.0, 5.0 , 5.0};
	
	//位移
	vec p = init_state;

	//渲染点个数
	int ii = 1000000;

	//配置文件
	std::ifstream cfg;
	cfg.open("config.ini");
	
	//解析配置文件
	if (cfg.good() == true)
	{
		config_parser p;
		p.parse(cfg);
		std::string p_a = p.query("param_a");
		std::string p_b = p.query("param_b");
		std::string p_c = p.query("param_c");
		std::string i_x = p.query("init_x");
		std::string i_y = p.query("init_y");
		std::string i_z = p.query("init_z");
		std::string p_dt = p.query("dt");
		std::string pnum = p.query("point_number");

		if (!p_a.empty()) a = std::stod(p_a);
		if (!p_b.empty()) b = std::stod(p_b);
		if (!p_c.empty()) c = std::stod(p_c);
		if (!i_x.empty()) init_state.x = std::stod(i_x);
		if (!i_y.empty()) init_state.y = std::stod(i_y);
		if (!i_z.empty()) init_state.z = std::stod(i_z);
		if (!p_dt.empty()) dt = std::stod(p_dt);
		if (!pnum.empty()) ii = std::stoi(pnum);
	}
	cfg.close();

	printf("Simulator.cpp C++\n\n");
	printf("lorenz parameter: a=%lf, b=%lf, c=%lf\n", a, b, c);
	printf("initialization_state -> (%lf, %lf, %lf)\n", init_state.x, init_state.y, init_state.z);
	printf("dt = %lf\n", dt);
	printf("number -> %d\n\n", ii);

	//输出文件
	std::ofstream f;
	f.open("output.obj");
	f.precision(9);
	f << std::fixed;
	f << "# Simulator.cpp C++ OBJ File: 'output.obj'" << std::endl;
	f << "o strange_attractor" << std::endl;

	//开始渲染
	printf("randering...");
	for (int i = 0; i < ii; ++i)
	{
		// v  在场中的速度
		// dp 位移微元
		// p  位移
		vec v = velocity(p);
		vec dp = v * dt;
		p = p + dp;
		f << "v" << ' ' << p.x << ' ' << p.y << ' ' << p.z << std::endl;
		printf("\r[%2.1lf%%|%5d] p -> (%2.9lf,%2.9lf,%2.9lf)", (double)i / ii * 100, i, p.x, p.y, p.z);
	}

	printf("\n");

	//处理点的关系
	for (int i = 1; i < ii; ++i)
	{
		f << "l" << ' ' << i << ' ' << i + 1 << std::endl;
		printf("\r %2.1lf%% generate line...", (double)i / ii * 100);
	}

	f.close();
}
