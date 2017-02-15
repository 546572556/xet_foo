#ifndef __QINIU_H
#define __QINIU_H

#define _op_qiniu_upload_notice_req   'QiniuUpLoadNoticeReq'
#define _op_qiniu_upload_notice_res   'QiniuUpLoadNoticeRes'


void QiniuUpLoadNoticeReq(THttpContent httpContent, TJson& jsonRes);
void HandleUserIconNotice(THttpContent httpContent, TJson& jsonRes);
void HandleConfNotice(THttpContent httpContent, TJson& jsonRes);

TInteger sendSync(TString destUrl, TString buf);

#endif
