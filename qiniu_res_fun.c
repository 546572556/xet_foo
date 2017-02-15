#include "qiniu.h"

TInteger sendSync(TString destUrl, TString buf)
{
  var THttpClient httpClient;
	var THttpContent httpContent;
	var TInteger ret;
	httpContent = new THttpContent;
	httpClient = new THttpClient('webxmlclient');
	print(sprintf('URL = %s-%s\n',destUrl,buf));
	httpContent.setbuffer('application/json', buf);
	try
	{
		ret = httpClient.sendpost(destUrl, httpContent, 30);
	}
	catch()
	{
	}
	ret = httpClient.getstatus();
	if(ret == 200)
	{
		print('success');
	}
	else
	{
		delete(httpContent);
		delete(httpClient);
		return -1;
	}
	delete(httpContent);
	delete(httpClient);
	return 0;
}

void QiniuUpLoadNoticeReq(THttpContent httpContent, TJson& jsonRes)
{
  var TString type;
  var TJson jsonReq;
  jsonReq = httpContent.getjsonbody()；

  type = jsonReq.getvalue('type','');
  /*
  *type: 0 icon,1 im group, 2 im point to point , 3 conference share document
  */
  if(type == '0') //icon
  {
    HandleUserIconNotice(httpContent, jsonRes);
  }
  else if(type == '1')
  {

  }
  else if(type == '2')
  {

  }
  else
  {

  }
}

void HandleUserIconNotice(THttpContent httpContent, TJson& jsonRes)
{
  var TJson jsonReq;
  var TString key,filename,filesize,mimetype,filetype,requestname,requestnum,uploadtime,type,sql;
  var TInteger ret;
  jsonReq = httpContent.getjsonbody()；
  filename = jsonReq.getvalue('filename','');
  key =  jsonReq.getvalue('key','');
  filesize = jsonReq.getvalue('filesize','');
  mimetype = jsonReq.getvalue('mimetype','');
  filetype = jsonReq.getvalue('filetype','');
  requestname = jsonReq.getvalue('requestname','');
  requestnum = jsonReq.getvalue('requestnum','');
  uploadtime = jsonReq.getvalue('uploadtime','');
  type = jsonReq.getvalue('type','');

  sql = sprintf('insert into qiniures(key,filename,filesize,mimetype,filetype,requestname,requestnum,type,uploadtime)
                            values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')', key, filename, filesize, mimetype,filetype, requestname, requestnum, type, uploadtime);
  ret = sqlrun(sql);
  if(ret < 0)
  {
    jsonRes.addchild('status', 'failed', '', 0);
  }
  //upload  user_info table
  sql = sprintf('update user_info set filePath=\'%s\' where userNum = \'%s\'', key, requestnum);
  jsonRes.addchild('status', 'success', '', 0);
  jsonRes.addchild('opType', _op_qiniu_upload_notice_res, '', 0);
}

void HandleIMNotice()
{

}
void HandleConfNotice(THttpContent httpContent, TJson& jsonRes)
{
  var TJson jsonReq;
  var TString key,filename,filesize,mimetype,filetype,requestname,requestnum,uploadtime,type,cid,confid,sql;
  var TString msg,destconfurl;
  var TInteger ret;
  jsonReq = httpContent.getjsonbody()；
  filename = jsonReq.getvalue('filename','');
  key =  jsonReq.getvalue('key','');
  filesize = jsonReq.getvalue('filesize','');
  mimetype = jsonReq.getvalue('mimetype','');
  filetype = jsonReq.getvalue('filetype','');
  requestname = jsonReq.getvalue('requestname','');
  requestnum = jsonReq.getvalue('requestnum','');
  uploadtime = jsonReq.getvalue('uploadtime','');
  type = jsonReq.getvalue('type','');
  cid = jsonReq.getvalue('clientfileid','')
  confid  = jsonReq.getvalue('confid','')

  sql = sprintf('insert into qiniures(key,filename,filesize,mimetype,filetype,requestname,requestnum,type,uploadtime)
                            values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')',key, filename, filesize, mimetype,filetype, requestname, requestnum, type, uploadtime);
  ret = sqlrun(sql);
  if(ret < 0)
  {
    jsonRes.addchild('status', 'failed', '', 0);
  }
  msg = sprintf('{"confId":"%s","fileName":"%s","fileSize":"%s","fileType":"%s","requestNum":"%s","clientFileId":"%s","key":"%s"}',confid,filename,filesize,filetype,requestnum,cid,key);
  //get  dest conf http url
  destconfurl = xmlwoods('SDSM:SDSM/SerVice/destPstnUrlSoap','');
  sendSync(destconfurl,msg);
  jsonRes.addchild('status', 'success', '', 0);
  jsonRes.addchild('opType', _op_qiniu_upload_notice_res, '', 0);
}
