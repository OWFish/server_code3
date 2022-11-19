#ifndef _FDOP_H_
#define _FDOP_H_

/************************************************************************
*
*                    �����ļ���Ŀ¼����������
*
************************************************************************/

namespace FDOP
{
	/* �ж��ļ���Ŀ¼�Ƿ����
	* �ڲ���ϵͳ�У�Ŀ¼Ҳ��һ���ļ������Ҫ�ж�һ��Ŀ¼�Ƿ������Ӧ��ʹ��DirectoryExists��
	* Ҫ�ж�һ���ļ��Ƿ��������һ���鵵�ļ���Ӧ��ʹ��IsArchive��
	* @����ļ���Ŀ¼�����򷵻�true���򷵻�false
	* %�ļ�·���ַ����Ȳ��ó���MAX_PATH
	*/
	bool FileExists(const char* sFilePath);
	
	/* ��㴴��Ŀ¼
	 * �������Ŀ¼C:\a\b\c\d������Ŀ¼�ĸ�Ŀ¼���������𼶴�����Ŀ¼����������Ŀ¼
	 * @���Ŀ¼��ȫ�����ɹ���������true�����򷵻�false��
	 * %����ڴ���ĳ����Ŀ¼�ɹ��󲢴�����Ŀ¼ʧ�ܣ���������false���Ѿ������ĸ�Ŀ¼���ᱻɾ����
	 * %Ŀ¼·���������ַ����ȣ�����Ҫ�������MAX_PATH���ַ���������
	 */
	bool DeepCreateDirectory(const char* sDirPath);

	
	/* ��ȡ�ļ�����Ŀ¼·��
     * c:\abc\efg\123.txt --> c:\abc\efg\
	 * c:\abc\efg\ --> c:\abc\
	 * ����sDirBuf���ڴ洢Ŀ¼�ַ���
	 * ����dwBufLenΪsDirName�����Ļ������ַ������ֽڣ����ȣ����к���Ҫ��������ֹ�ַ���
	       ���dwBufLenֵΪ0�������ὫĿ¼·��������sDirBuf�У�
		   ���dwBufLenֵ��0�����ὫĿ¼·��������sDirBuf�в�����sDirBuf��д����ֹ��;
		   ���������������ֻ����dwBufLen-1���ַ�������sDirBuf��д����ֹ����
		@�������ؿ���Ŀ¼·��������ַ����ȣ�����ֹ����
	 */
	size_t ExtractFileDirectory(const char* sFilePath, char* sDirBuf, size_t dwBufLen);

	/* ��ȡ����Ŀ¼����
	 * (abc\efg\ --> abc)
	 * ����ppChildDirPath���ڴ涥��Ŀ¼֮���Ŀ¼·������������Ϊ��
	 * ����sDirName���ڴ洢Ŀ¼�ַ���
	 * ����dwBufLenΪsDirName�����Ļ������ַ������ֽڣ����ȣ����к���Ҫ��������ֹ�ַ���
	       ���dwBufLenֵΪ0�������ὫĿ¼��������sDirName�У�
		   ���dwBufLenֵ��0�����ὫĿ¼��������sDirName�в�����sDirName��д����ֹ��;
		   ���������������ֻ����dwBufLen-1���ַ�������sDirName��д����ֹ����
		@�������ؿ���Ŀ¼��������ַ����ȣ�����ֹ����
	 */
	size_t ExtractTopDirectoryName(const char* sDirPath, const char* *ppChildDirPath, char* sDirName, size_t dwBufLen);

	/* ��ȡ�ļ���Ŀ¼����
	 * c:\abc\123.txt --> 123.txt
	 * c:\abc\efg\ --> efg
	 * ����sDirBuf���ڴ洢�ļ������ַ���
	 * ����dwBufLenΪsNameBuf�����Ļ������ַ������ֽڣ����ȣ����к���Ҫ��������ֹ�ַ���
		    ���dwBufLenֵΪ0�������Ὣ�ļ���������sNameBuf�У�
		    ���dwBufLenֵ��0�����Ὣ�ļ���������sNameBuf�в�����sNameBuf��д����ֹ��;
		    ���������������ֻ����dwBufLen-1���ַ�������sNameBuf��д����ֹ����
		@�������ؿ����ļ���������ַ����ȣ�����ֹ����
	*/
	size_t ExtractFileName(const char* sFilePath, char* sNameBuf, size_t dwBufLen);
}

#endif
