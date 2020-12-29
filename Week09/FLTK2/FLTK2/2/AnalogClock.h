//��дһ��ģ��ʱ�ӣ���һ������ת��ָ���ʱ�ӡ�ͨ��һ���⺯�����ôӲ���ϵͳ��ȡʱ��ֵ����ʾ��clock()��sleep()
//Ҫ��
//���Ƶ�ģ��ʱ�Ӻ���ʵʱ��һ�£�����ʱ / �� / ���룬12��Сʱ�Ŀ̶ȼ���Ӧ����
//��ʱ������ʾ���ڣ��� / �� / �գ��Լ���ǰʱ��
#define _CRT_SECURE_NO_WARNINGS
#include "../revised-gui/Simple_window.h"    // get access to our window library
#include "../revised-gui/Graph.h"            // get access to our graphics library facilities
#define CENTER 300							 // ���ĵ�λ��
#define FONTSIZE 25							 // �ֺ�
const double PI = acos(-1);					 // Բ����

using namespace Graph_lib;

// ��ȡ�������λ
Point converter(int length, double angle);

// ָ��
struct Pointer : Closed_polyline
{
	Pointer(int _length, double _angle, int _width);
private:
	void draw_lines() const;
	int			length;						// ����
	double		angle;						// �Ƕ��ƽǶȣ�˳ʱ�붨�壩
	int			width;						// ָ����
	Point		tip;						// ���λ��
};

// ģ��ʱ��
class AnalogClock: public Shape {
public:
	AnalogClock();
	~AnalogClock();
	// ��ȡ����
	string getDate(tm* p) const;
	// ��ȡʱ��
	string getTime(tm* p) const;
	// ��ȡʱ��Ƕ�
	double getHAngle(tm *p) const;
	// ��ȡ����Ƕ�
	double getMAngle(tm* p) const;
	// ��ȡ����Ƕ�
	double getSAngle(tm* p) const;
private:
	// �Ƕ�ӳ��
	double AngleMap(double _progress) const;
	// ˫λ����
	string dualFiller(int _input) const;
	void draw_lines() const;
};