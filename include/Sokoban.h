#pragma once
/*��������Ϸ
��飺
	�򵥵���������Ϸ�������������Ƶ�Ŀ�ĵؼ���

��Ϸ���ű�ǣ�
	�ϰ��#
	����*
	���ӣ�$
	Ŀ�ĵأ�@
	����+Ŀ�ĵأ�!
	����+Ŀ�ĵ�: R

��Ϸ���ƣ�
	�������Ҽ������ƶ�����
*/
class Sokoban
{
public:
	Sokoban();;
	~Sokoban() {};

private:
	int width, height; // ��Ϸ��ͼ�Ŀ�͸�
	int boxAmount = 5; // ��Ϸ�����ӵ�������Ŀ�ĵص�����
	int successCount; // ���ڱ�Ƕ��������Ʒŵ�Ŀ�ĵ��ˣ������ж���Ϸ�Ƿ����
	char** area; // �ַ���ά���飬��Ϸ��ͼ
	int seed; // ��������ӣ��õ�ǰʱ������������ɲ�ͬ�������
	int wallAmount; // ��Ϸ��ǽ������

	/*������Ϸ����ӡ��ά����*/
	void redraw();
	/*��ȡ�û����룬���������ƶ�*/
	bool controller();
	/*��ʼ����ͼ*/
	void initArea();
	/*�����������*/
	void initMan();
	/*��������ϰ���ǽ*/
	void initWalls();
	/*�����������*/
	void initBoxs();
	/*�������Ŀ�ĵ�*/
	void initTargets();
	/*�������λ��*/
	int* createRandPosition();
	/*�����������λ�ã����Ӳ����������ǽ*/
	int* createRandBoxPosition();
	/*���������ƶ�*/
	void up();
	/*���������ƶ�*/
	void down();
	/*���������ƶ�*/
	void left();
	/*���������ƶ�*/
	void right();
	/*���ҷ�����������*/
	int* findMan();
	/*���ӻ���������ƶ��任*/
	void move(int* currentPos, int* nextPos);
	/*�ж���Ϸ�Ƿ��������successCount�Ƿ����boxAmount*/
	bool isOver();
};

