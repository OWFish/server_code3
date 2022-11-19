#pragma once

#define BEGIN_GET_ROW() \
	MYSQL_ROW pRow = sql_->CurrentRow();\
	int rowCount = sql_->GetRowCount();\
	unsigned long *fieldLength = sql_->GetFieldsLength();

#define  GET_NEXT_FIELD_LENGTH() \
		fieldLength = sql_->GetFieldsLength();

#define GetIntRow(i,data) if(pRow[i]!=NULL) sscanf(pRow[i],"%d",&(data))
#define GetDataRow(i,data) if(pRow[i]!=NULL) memcpy(&(data),pRow[i],__min(fieldLength[i],sizeof(data)))
#define GetLIntRow(i, data) if(pRow[i]!=NULL)  data = atoll(pRow[i]);
#define GetDoubleRow(i, data) if(pRow[i]!=NULL) sscanf(pRow[i], "%lf", &(data))
#define GetStringRow(i, data) if(pRow[i]!=NULL) sscanf(pRow[i], "%s", &(data))

#define FirstData(data,size) sprintf(fieldbuf, "\""); mysql_escape_string(&fieldbuf[2], (const char*)(&data), (unsigned long)size); strcat(fieldbuf,"\"");strcat(databuf, fieldbuf) 
#define FirstInt(v) sprintf(fieldbuf, "%d", v); strcat(databuf, fieldbuf)
#define FirstLInt(v) strcat(databuf, std::to_string(v).c_str()); 
#define AddData(data,size) sprintf(fieldbuf, ",\""); mysql_escape_string(&fieldbuf[2], (const char*)(&data), (unsigned long)size); strcat(fieldbuf,"\"");strcat(databuf, fieldbuf) 
#define AddInt(v) sprintf(fieldbuf, ",%d", v); strcat(databuf, fieldbuf)
#define AddLInt(v) sprintf(fieldbuf, ",%lld", v); strcat(databuf, fieldbuf)

#define FirstSetInt(name,v) sprintf(fieldbuf, "`%s`=%d ", name,v); strcat(huge_buf_s, fieldbuf);
#define FirstSetLInt(name,v) sprintf(fieldbuf, "`%s`=%lld ", name,v); strcat(huge_buf_s, fieldbuf);
#define FirstSetData(name,data) sprintf(fieldbuf, "`%s`=\"", name); strcat(huge_buf_s, fieldbuf); mysql_escape_string(fieldbuf, (const char*)(&data); strcat(fieldbuf,"\" "); strcat(huge_buf_s, fieldbuf);
#define SetInt(name,v) sprintf(fieldbuf, ",`%s`=%d ", name,v); strcat(huge_buf_s, fieldbuf);
#define SetLInt(name,v) sprintf(fieldbuf, ",`%s`=%lld ", name,v); strcat(huge_buf_s, fieldbuf);
#define SetData(name,data,size) sprintf(fieldbuf, ",`%s`=\"", name); strcat(huge_buf_s, fieldbuf); mysql_escape_string(fieldbuf, (const char*)(&data), (unsigned long)size); strcat(fieldbuf,"\" "); strcat(huge_buf_s, fieldbuf);
#define SetString(name,v) sprintf(fieldbuf, ",`%s`='%s' ", name,v); strcat(huge_buf_s, fieldbuf);
