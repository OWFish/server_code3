#ifndef _DEF_EXCEPT_HANDLE_H_
#define _DEF_EXCEPT_HANDLE_H_

/************************************************************************/
/* 
/*                    Ĭ�Ͼֲ��쳣�����¼������
/*
/*   ��������__try ... __except���ж��쳣���м�¼���ָ������ִ�С�DefaultExceptHandler
/* �������ʽ�����ֳ������쳣���Ͳ��ڵ��������Լ�ͨ��OutputMsg��������쳣��¼��
/*
/*   ʹ��ʾ����
/*   __try
/*   {
/*      //�����κο��ܲ����쳣�Ĵ����������
/*   }
/*   __except(DefaultExceptHandler(GetExceptionInformation()))
/*   {
/*      //���쳣������Ĵ������
/*   }
/*
/************************************************************************/
DWORD DefaultExceptHandler(const LPEXCEPTION_POINTERS lpPointers);

#endif

