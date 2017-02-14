#include "qiniu.h"

void QiniuUpLoadNoticeReq(THttpContent httpContent, TJson& jsonRes)
{
  var TString type;
  var TJson jsonReq;
  jsonReq = httpContent.getjsonbody()；

  type = jsonReq.getvalue('type','');
  /*
  *type: 0 icon,1 im , 2 conference share document
  */
  if(type == '0') //icon
  {

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
                            values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')');
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
void HandleConfNotice()
{


}
