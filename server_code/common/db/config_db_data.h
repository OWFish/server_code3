#ifndef _CONFIG_DB_DATA_H_
#define _CONFIG_DB_DATA_H_

#define  MAX_NAME_LEN 64

#define MAX_LEN_BUFF 64

#define MAX_LEN_DESC 1024


//������ݽṹ
typedef struct staticaward
{
	int itemid;   		//�����Ʒid
	int needgrid;		//��Ҫ������
	char itemname[MAX_NAME_LEN];
	char itemdesc[MAX_LEN_DESC];
	//int itype; //��Ʒ����
	//int sell_type;
	int icon; //ͼ��id
	//int color;
	//int dura;
	int dup;  //��Ʒ�����ص�����
	//int colGroup;
	//int dealType;
	//int dealPrice;
	int itime;  //ʹ������
	unsigned int flag; //�����ݿ�ʱ����һ���Ѿ����λ��
	int grouptype;			//�������ͣ�û���û�0��ʾ���������飬��ȫ������,1��ʾ����������
	int cond_cons_id;    	//������������Ʒid,û����0
	int cond_cons_count; 	  //������������Ʒid����,û����0
	int cond_money_type;			//��������������Ǯ���ͣ�û����0
	int cond_money_count;	//	��������������Ǯ������û����0
	char cond_value[MAX_LEN_BUFF]; //���ַ�����ʾ������ c1=v1&c2=v2&c3=v3����������ʽ
} Staticaward_t;
//�������
typedef struct staticawardconfig
{
	int giftitemid; //	�����Ʒid
	int rewardtype;	//�������� 1 ��Ʒ 2 ��Ǯ ... ������Զ���
	int contenttype;// �������ݵ�����  Ŀǰֻ������Ǯ����
	int amount;    // �������� ��Ʒ����  ����  ���
	int itemid;		//�������id������Ʒid����id��
	int bind; 			//�Ƿ�󶨣�0��ʾ�ǰ�1��ʾ��
	int group;  				//	������
	int rate;		//�������
	int noworldrate;		//�Ƿ����羭��ӳɣ�0�ӳɣ�1��ʾ���޼ӳ�
	int quality;
	int strong;
}Staticawardconfig_t;





#endif

