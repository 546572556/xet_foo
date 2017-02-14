#progma c

#import "cinhttp"

void main(TObject reqObject)
{
  var THttpServer httpServer;
  var THttpContent httpContent,httpContentRes;
  var TJson jsonReq,jsonRes;
  var TString opType;
  if(reqObject.type() != TObject::HttpServerType)
  {
    return;
  }
  jsonRes = new(TJson);
  jsonRes.init();
  jsonRes.setcurrentpath('JSON');

  httpServer = (THttpServer)reqObject;
  httpContent = httpServer.getcontent();
  jsonReq = httpContent.getjsonbody();
  print('jsonReq: '+jsonReq.tostr());
  opType = jsonReq.getvalue('opType','');
  switch(opType)
  {
    case _op_qiniu_upload_notice_req:
    {
      QiniuUpLoadNoticeReq(httpContent, jsonRes)
      break;
    }
  }

	httpContentRes = new THttpContent;
	httpContentRes.setjsonbody(jsonRes);
	httpServer.sendstatusresponse(200, httpContentRes);
  delete(httpContentRes);
  delete(jsonRes)；
}
