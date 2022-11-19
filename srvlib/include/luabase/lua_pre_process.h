#ifndef _LUA_PRE_PROCESS_H_
#define _LUA_PRE_PROCESS_H_

/****************************************************************

                   ͨ��LUA�ű��ı�����Ԥ������

    ����LUA�ʷ������������д����ı�Ԥ����Ĺ�������ʵ����������Ҫ�õ����������
  ����C���Ե�Ԥ�����ܣ�����ṩ�������ڶԽű��ı����ݽ��м򵥵�Ԥ����Ϊ��ʹ
  Ԥ����ָ��Ĵ����﷨����lua�﷨������������HTML����дJavaScript����ķ�ʽ��
  ʹ��ԭ�����Ե�ע���﷨ʵ��Ԥ�����﷨����luaԤ��������Ԥ����ָ����﷨�������£�
  --#directive implemente data
    ����Ԥ����ָ��������п�ʼ�ĵ�һ���ַ�����д��һ��Ԥ����ָ��ó���һ�С�Ԥ
  ����ָ���ǲ����ִ�Сд�ġ�

  Ԥ����Ŀǰʵ�������й��ܣ�
    1�������ļ�������ʹ�á�--#include "FilePath"��������һ�������ļ���
	  �����ļ�������˳�������ȴӵ�ǰ�ļ���Ŀ¼��ʼʹ�����·������������Ҳ���
	  �ļ�����Ԥ��Ĵ����ļ�����Ŀ¼�н���������Ŀ¼�������������ָ�����֧��
	  �����ճ���Ϊ1024���ַ���·�����д���
	2���궨�壬ʹ�á�--#define NAME [VALUE]��������һ���꣬���ֵ���ַ�����
	  ��--#undef NAME����ȡ��һ����Ķ��塣������Ƴ��Ȳ��ó���30���ַ������ֵ
	  ���Ȳ��ó���126���ַ���
    3�����ں��������⣬ʹ�á�--#ifdef������--#ifndef������--#if MACRO == VALUE����
	   ��--#if MACRO != VALUE������--#else������--#elif������--#endif����

****************************************************************/
class LuaPreProcessor :
	public stream::MemoryStream
{
public:
	typedef MemoryStream Inherited;
	/* ����Դ�ļ��к���Ϣ */
	struct LineRange
	{
		char sFileName[256]; //Դ�ļ�·��������MAX_PATH��ʹ�ö��ļ���
		int nLineStart; //Ԥ��������ʼ�к�
		int nLineEnd;	//Ԥ�����Ľ����к�
	};
	class LineRangeList : public container::Vector<LineRange>
	{
	public:
		/* ��ȡԤ�������кŶ�Ӧ��ԭʼ�ļ�·���Լ��к�
		* nLineNo Ԥ�������кţ��кŴ�1��ʼ
		* nSrcLineNo ���ڱ���ԭʼ�ļ��кţ��кŴ�1��ʼ
		* @return ����ҵ���Ӧ���кţ����������ļ�·���ַ���ָ�벢�����nSrcLineNoΪԭʼ�ļ��кţ�����������NULL
		*/
		const char* getSourceLineNumber(int nLineNo, int& nSrcLineNo);
	};
public:
	LuaPreProcessor(BaseAllocator* alloc);
	~LuaPreProcessor();

	/* ������ű����ݽ���Ԥ����
	 *sSourceText	�����ַ�����ʼָ�룬�����ַ���������0��β��
	 *sFilePath		���������ļ������ļ���������·�������ڽ������Ȱ���Ŀ¼����
	 *cNewLine		�����ַ���Ĭ��ֵΪ'\n'
	 *@return ���ش������ַ���ָ�룬�ַ�����Ԥ���������ٻ�����´η���֮ǰһֱ��Ч
	 */
	const char* parse(const char* sSourceText, const char* sFilePath, const char cNewLine = '\n');

	//��Ӱ����ļ�����Ŀ¼
	void addIncludeDirectory(const char* sPath)
	{
		m_IncludeDirList.add(new String(sPath));
	}
	//��հ����ļ�����Ŀ¼
	void clearIncludeDirectory();
	/* ���Ԥ����궨��
	 * sName		������
	 * sValue		�����ֵ
	 */
	void addMacro(const char* sName, const char* sValue = NULL);
	//�Ƴ�һ���궨��
	void removeMacro(const char* sName);
	//���Ԥ����궨��
	void clearMacroList();
	/* ��ȡԴ�ļ��кŶ��ձ�
	 * pLineRange ���ڱ����ļ��к���Ϣ�Ļ�����
	 * nCount �������пɴ洢���к���Ϣ����
	 *@return ���pLineRangeΪ�գ��������ر������е�����Ϣ������к���Ϣ����������������ֵΪʵ����pLineRange�п�������Ϣ����
	 */
	int getLineRangeData(LineRange* pLineRange, int nCount);
	/* ��ȡԤ�������кŶ�Ӧ��ԭʼ�ļ�·���Լ��к�
	* nLineNo Ԥ�������кţ��кŴ�1��ʼ
	* nSrcLineNo ���ڱ���ԭʼ�ļ��кţ��кŴ�1��ʼ
	* @return ����ҵ���Ӧ���кţ����������ļ�·���ַ���ָ�벢�����nSrcLineNoΪԭʼ�ļ��кţ�����������NULL
	*/
	const char* getSourceLineNumber(int nLineNo, int& nSrcLineNo);
	void clearMacro()
	{
		m_MacroList.clear();
	}
protected:
	/* ������ǰ�������ڲ����µ�����ű����ݽ���Ԥ����
	 *sSourceText	�����ַ�����ʼָ�룬�����ַ���������0��β��
	 */
	const char* ParseSource(const char* sSourceText);
	//���浱ǰԤ��������������������������ѹ�뻷��ջ��
	inline void SaveParseEnvir()
	{
		m_ParseEnvirStack.add(m_ParseEnvir);
	}
	//�ָ���һ��Ԥ�����������������ָ���ɾ��ջ���ķ�����������
	inline void RestorsParseEnvir()
	{
		m_ParseEnvir = m_ParseEnvirStack[m_ParseEnvirStack.count() - 1];
		m_ParseEnvirStack.trunc(m_ParseEnvirStack.count() - 1);
	}
	//�����ԡ�--#���ı���ͷ��Ԥ������
	void ProcessLine(const char* sLineText);
	/* ����ִ��Ԥ����ָ��Ĺ���
	 * ���������Ҫ����ʵ�ָ����Ԥ����ָ����޸�����Ԥ����ָ���ʵ�ֹ�������Ը��Ǵ˺���
	 */
	void ProcessDirective(const char* sDirective, const char* sData);
	//��#includeԤ����ָ��ܵ�ʵ��
	void DirectiveOfInclude(const char* sData);
	//��#defineԤ����ָ���ʵ��
	void DirectiveOfDefine(const char* sData);
	//��#undefԤ����ָ���ʵ��
	void DirectiveOfUndef(const char* sData);
	//��#ifdefԤ����ָ���ʵ��
	void DirectiveOfIfdef(const char* sData);
	//��#ifndefԤ����ָ���ʵ��
	void DirectiveOfIfndef(const char* sData);
	//��#ifԤ����ָ���ʵ��
	void DirectiveOfIf(const char* sData);
	//��#elseԤ����ָ���ʵ��
	void DirectiveOfElse(const char* sData);
	//��#elifԤ����ָ���ʵ��
	void DirectiveOfElif(const char* sData);
	//��#endifԤ����ָ���ʵ��
	void DirectiveOfEndif(const char* sData);

protected:
	//Ԥ�������ʶ�����
	typedef char PPToken[128];

	/*** �﷨���������������� ***/
	/*
	* Comments: ���ո��WhiteSpace�ָ��
	* Param const char* sLinePtr: �����ı����ַ���ָ��
	* Param IN OUT const char* * sTokens: ���ڴ洢ÿ���ʵ�ָ����ַ�������
	* Param IN OUT int & nTokenCount: �޶����ȡ��������ȡ����ɺ�˲���������ʵ��ȡ�Ĵ�����
	* @Return const char*: ���ؾ���ȡ�ʺ���������sLinePtr��λ�ã��Ա���ڷ���ֵ����ȡ��
	*/
	const char* delimiteLine(const char* sLinePtr, PPToken* sTokens, int& nTokenCount);
	//��ȡ��ȫ��Ԥ����ȡ������ֵ
	void refreshCondition();
	//���ִ��󣬱����ֹ����
	inline void abort()
	{
		m_boErrorAbort = true;
	}
	//����Ѱ����ļ��б�
	void clearIncludedFileList();

protected:
	//�������ĺ���
	virtual void showError(const char* sError);
	//��������ʽ�����������ĺ���
	virtual void showErrorFormat(const char* sFmt, ...);
private:
	/* ������ǰ�������ڲ����µ�����ű����ݽ���Ԥ����
	 * ��������ǰ��ȡ�ô����ļ���Ŀ¼��ѹ��Ԥ�����������ļ�����ջ�У��������ջ�н�Ŀ¼�Ƴ�
	 *sSourceText	�����ַ�����ʼָ�룬�����ַ���������0��β��
	 *sFillFilePath	�����ļ�������·��
	 */
	const char* SaveFileDirAndParse(const char* sSourceText, const char* sFillFilePath);
	//���������ذ����ļ�
	bool SearchAndLoadIncludeFile(const char* fn, bool mul);
	//���ز����������ļ�
	bool LoadIncludeFile(const char* sIncludeFilePath, bool boEnableMultipleInclude);

protected:
	//Ԥ��������������
	typedef struct tagPreProcParseEnvir
	{
		const char* sFilePath;		//ԭʼ�ļ�·��
		const char*	sParsePtr;		//�������ݷ���λ��
		const char* sNewLinePtr;	//����λ��
		const char* sLineEndPtr;	//��βλ��
		int nLineNo;		//��ǰ�������кţ���1��ʼ
		tagPreProcParseEnvir() : sFilePath(NULL),
			sParsePtr(NULL), sNewLinePtr(NULL), sLineEndPtr(NULL),
			nLineNo(0)
		{
		}
	} PREPROC_PARSERENVIR, *PPREPROC_PARSERENVIR;
	//Ԥ�������еĺ궨��
	typedef struct tagMacro
	{
		char	sName[32];
		char	sValue[128];
	} PREPROC_MACRO, *PPREPROC_MACRO;

	PREPROC_PARSERENVIR						m_ParseEnvir;		//��ǰ��������
	container::Vector<PREPROC_PARSERENVIR>	m_ParseEnvirStack;	//Ԥ������������������б�����ȳ�
	container::Vector<String*>				m_FilePathStack;	//Ԥ�����������ļ�����ջ������ȳ�
	container::Vector<String*>				m_IncludeDirList;	//������Ԥ���Ԥ��������ļ�����Ŀ¼�б�
	container::Vector<PREPROC_MACRO>		m_MacroList;		//Ԥ������б�
	container::Vector<bool>					m_ConditionList;	//��ǰԤ����������
	container::Vector<const char*>			m_IncludedFileList;	//Ԥ�������Ѿ����������ļ��б�
	LineRangeList							m_LineRangeList;	//Դ�ļ��к���Ϣ��
	int										m_nLineNo;			//��ǰ�ܼ��ļ��к�
	char									m_NewLineChar;		//���з���Ĭ����'\n'
	bool									m_boErrorAbort;		//�Ƿ���������Ҫ��ֹ����
	bool									m_boCurrCondition;	//��ǰ��Ԥ��������ֵ
public:
	//ͨ�������ƻ�ȡ��ָ��
	const PPREPROC_MACRO getMacro(const char* sName);
};

#endif

