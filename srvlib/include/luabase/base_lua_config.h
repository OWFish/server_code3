#ifndef _BASE_LUA_CONFIG_H_
#define _BASE_LUA_CONFIG_H_

class BaseLuaConfig
	: public BaseLua
{
public:
	typedef BaseLua Inherited;
	typedef misc::RefObjectImpl<String> TableName;
private:
	container::Vector<TableName*>	m_TableStacks;	//�Ѵ򿪱������б�

public:
	bool ExcuteCjson(const char* funcname, const char* p1, const char* p2, const char* p3);
protected:
	//��ʾ�ű���������
	void showError(const char* sError);
	//��ʾ�����ڵĴ���
	void showTableNotExists(const char* sTableName);
	//��ʾû�а�����Чֵ�Ĵ���
	void showFieldDoesNotContainValue(const char* sFieldName, const char* sValueType);
	//ͨ��const char*�ַ�������һ��TableName
	static TableName* createTableName(const char* sName);
protected:
	/*	�򿪽ű��ڵ�ȫ�ֱ��ɹ��򷵻�true��ʧ�ܻ�����showError��
		������ʹ��һ���Ѿ��򿪵ı��ʱ�����ʹ��closeTable����رա�
	*/
    bool openGlobalTable(const char* sTableName);
	/*	�򿪵�ǰ���е��ӳ�Ա���ɹ��򷵻�true��ʧ�ܻ�����showError��
		������ʹ��һ���Ѿ��򿪵ı��ʱ�����ʹ��closeTable����رա�
	*/
    bool openFieldTable(const char* sTableName);
	/*	��ʼ������ǰ�Ѿ��򿪵ı�
		������ȴ���0��ʼ����������true��
	*/
    bool enumTableFirst();
	/*  ����������ǰ�Ѿ��򿪵ı�
		��һ����ĵ�һ�α�������ʹ��enumTableFirst�����ļ���������ʹ��enumTableNext��
		����Ѿ���������Ľ�β����������FALSE����ʱ���õ���enumTableNext���ڱ�ö�ٽ�
		��ʱ�Ѿ��Զ�����ر��ˡ�
	*/
    bool enumTableNext();
	/*	��ֹ�Ե�ǰ���ö�١�
		�ڵ���enumTableFirst��ʼ�Ա�ı������ڱ����п���ʹ��enumTableNext��������ֱ��
		�䷵��false��
		����ڱ����ڼ���Ҫ��ֹ�Ա�ı�������Ӧ��ʹ��enumTableNext��������ı�����
	*/
    void endTableEnum();
	/*	����ǰ���еĵ�IndexStartFromOne�����ĸ���Ա������򿪡��ɹ��򷵻�true��ʧ�ܻ�����showError��
		IndexStartFromOne�����Ǵ�1��ʼ�ģ�����ѭlua���Ե�������׼��������в�����IndexStartFromOne
		��Ա����ֵ����һ�����򷵻�FALSE������showError��
	*/
    bool getFieldIndexTable(const int IndexStartFromOne);
	/*	���Ե�ǰ�����Ƿ������ΪsTableName���ֳ�Ա��������ڴ����Ƶĳ�Ա��ֵ��һ�������ͣ��򷵻�true��
	*/
    bool feildTableExists(const char* sTableName);
	/*	�رյ�ǰ�򿪵ı�	*/
    void closeTable();
	/*	��ȡ��ǰ�Ѿ��򿪵ı������·����·���ָ��Ϊ'.' 
		����ֵ��Retval��ͬ������·�����洢��Retval�в���Ϊ����ֵ��
	*/
    String& getTablePath(String& Retval);
	/*	�ڱ�ö�ٹ����л�ȡ��ǰö�ٳ�Ա������
		����ֻ�ڱ��ö�ٹ�������Ч
	*/
	string::AnsiString& getKeyName(string::AnsiString& Retval);
	/*  ��ȡ��ö�ٳ��л�ȡ��ǰö�ٳ�Աֵ����������
		����ֻ�ڱ��ö�ٹ�������Ч
	*/
	inline int getValueType(){ return lua_type(lua_, -1); }
	/*	��ȡ������ΪsFieldName�Ĳ���ֵ��
		���sFieldName����ֵΪNULL�����ʾ��ȡͨ��enumTableFirst��enumTableNext���б�ö�ٵ�
		��ǰλ�õ�ö�ٳ�Ա��ֵ��
		���ֵ������ֵ�������ǲ������򷵻ؽű��е�ֵ����pIsValid�����д洢true��
		���ֵ�����ڻ����Ͳ���ת��Ϊ�������򷵻�Ĭ��ֵ����pIsValid�����д洢false�����Ĭ��ֵ�����ڣ��򷵻�false��
	*/
	bool getFieldBoolean(const char* sFieldName, const bool* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	��ȡ������ΪsFieldName������ֵ��
		���sFieldName����ֵΪNULL�����ʾ��ȡͨ��enumTableFirst��enumTableNext���б�ö�ٵ�
		��ǰλ�õ�ö�ٳ�Ա��ֵ��
		���ֵ������ֵ�����������֣������򸡵��������򷵻ؽű��е�ֵ����pIsValid�����д洢true��
		���ֵ�����ڻ����Ͳ���ת��Ϊ���֣��򷵻�Ĭ��ֵ����pIsValid�����д洢false�����Ĭ��ֵ�����ڣ��򷵻�0��
	*/
    double getFieldNumber(const char* sFieldName, const double* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	��ȡ������ΪsFieldName��64λ����ֵ��
		���sFieldName����ֵΪNULL�����ʾ��ȡͨ��enumTableFirst��enumTableNext���б�ö�ٵ�
		��ǰλ�õ�ö�ٳ�Ա��ֵ��
		���ֵ������ֵ�����������֣������򸡵��������򷵻ؽű��е�ֵ����pIsValid�����д洢true��
		���ֵ�к���С����������С�����֡�
		���ֵ�����ڻ����Ͳ���ת��Ϊ���֣��򷵻�Ĭ��ֵ����pIsValid�����д洢false�����Ĭ��ֵ�����ڣ��򷵻�0��
	*/
    int64_t getFieldInt64(const char* sFieldName,const int64_t* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	��ȡ������ΪsFieldName��32λ����ֵ��
		���sFieldName����ֵΪNULL�����ʾ��ȡͨ��enumTableFirst��enumTableNext���б�ö�ٵ�
		��ǰλ�õ�ö�ٳ�Ա��ֵ��
		���ֵ������ֵ�����������֣������򸡵��������򷵻ؽű��е�ֵ����pIsValid�����д洢true��
		���ֵ�к���С����������С�����֡�
		���ֵ�����ڻ����Ͳ���ת��Ϊ���֣��򷵻�Ĭ��ֵ����pIsValid�����д洢false�����Ĭ��ֵ�����ڣ��򷵻�0��
	*/
    int getFieldInt(const char* sFieldName, const int* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	��ȡ������ΪsFieldName���ַ���ֵ��
		���sFieldName����ֵΪNULL�����ʾ��ȡͨ��enumTableFirst��enumTableNext���б�ö�ٵ�
		��ǰλ�õ�ö�ٳ�Ա��ֵ��
		���ֵ������ֵ�����Ϳ���Ϊ�ַ���ֵ���򷵻ؽű��е��ַ���ָ�벢��pIsValid�����д洢true��
		�ﷵ�ص��ַ���ָֻ�ڽű��е�ֵ���ݷ����ı�֮ǰ��Ч������ű����ݲ���ı䣬����Գ���ʹ��
		���ص�ָ�룬�����ڻ�ȡ�ַ���ָ�����뽫���ݿ�������Ч���ڴ��ַ������ű����޸��ҽ���
		���������ն�ʹ���ַ���ָ�벻����Ч�Ӷ������ڴ����
		���ֵ�����ڻ����Ͳ���ת��Ϊ�ַ������򷵻�Ĭ��ֵ����pIsValid�����д洢false�����Ĭ��ֵ�����ڣ��򷵻�NULL��
	*/
    const char* getFieldString(const char* sFieldName, const char* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	��ȡ������ΪsFieldName���ַ���ֵ��
		���sFieldName����ֵΪNULL�����ʾ��ȡͨ��enumTableFirst��enumTableNext���б�ö�ٵ�
		��ǰλ�õ�ö�ٳ�Ա��ֵ��
		���ֵ������ֵ�����Ϳ���Ϊ�ַ���ֵ�����ַ������ݿ�����sBuffer�У������ؿ������ַ������ȣ�
		�����ַ����ĳ�����dwBufLen�������ƣ�dwBufLen������sBuffer����󳤶ȣ����ǻ������ֽڳ��ȡ�
		��������е�ֵ�ĳ��ȳ���dwBufLen-1����ֻ����dwBufLen-1�ĳ��ȡ�
		������Σ�ֻҪdwBufLen����0�������ڿ���ֵ֮��ΪsBuffer�����ֹ�ַ���
		���ֵ�����ڻ����Ͳ���ת��Ϊ�ַ������򷵻�-1�����Retval���ڴ��ַ��Ч���������ַ�Ϊ0��
	*/
	int getFieldStringBuffer(const char* sFieldName, char* sBuffer, size_t dwBufLen);
public:
	BaseLuaConfig();
	virtual ~BaseLuaConfig();
};

#endif
