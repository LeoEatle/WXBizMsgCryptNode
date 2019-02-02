#include <iostream>
#include <string>
#include "WXBizMsgCrypt.h"

using namespace Tencent;
using namespace std;
using namespace tinyxml2;

/*
*read me
*��ʾ������Ӧ���˿�Դ��openssl��tinyxml2�⣬�������32λ��64λ�ľ�̬������,
*ʾ��Makefile������������64λ�汾�ģ������Ի���Ϊ32λ�����Makefile������

*openssl�İ汾����openssl-1.0.1h��http://www.openssl.org/
*tinyxml2�İ汾����tinyxml2-2.1.0,    https://github.com/leethomason/tinyxml2,  �ÿ���lib��include�����Ƿ���cpp�ļ��ġ�
*/

int main()
{
	// ������ҵ����ҵ΢�ź�̨���õĲ�������
	string sToken = "QDG6eK";
	string sCorpID = "wx5823bf96d3bd56c7";
	string sEncodingAESKey = "jWmYm7qr5nMoAUwZRjGtBxmz3KA1tkAj3ykkR6q2B2C";	

	/*
	------------ʹ��ʾ��һ����֤�ص�URL---------------
	*��ҵ�����ص�ģʽʱ����ҵ΢�Ż�����֤url����һ��get���� 
	��������֤ʱ����ҵ�յ���������
	* GET /cgi-bin/wxpush?msg_signature=5c45ff5e21c57e6ad56bac8758b79b1d9ac89fd3&timestamp=1409659589&nonce=263014780&echostr=P9nAzCzyDtyTWESHep1vC5X9xho%2FqYX3Zpb4yKa9SKld1DsH3Iyt3tP3zNdtp%2B4RPcs8TgAE7OaBO%2BFZXvnaqQ%3D%3D 
	* HTTP/1.1 Host: qy.weixin.qq.com

	���յ�������ʱ����ҵӦ	1.������Get����Ĳ�����������Ϣ��ǩ��(msg_signature)��ʱ���(timestamp)��������ִ�(nonce)�Լ���ҵ΢�����͹�������������ַ���(echostr),
	��һ��ע����URL���롣
	2.��֤��Ϣ��ǩ������ȷ�� 
	3. ���ܳ�echostrԭ�ģ���ԭ�ĵ���Get�����response�����ظ���ҵ΢��
	��2��3����������ҵ΢���ṩ�Ŀ⺯��VerifyURL��ʵ�֡�
	*/
    WXBizMsgCrypt wxcpt(sToken,sEncodingAESKey,sCorpID);
	// string sVerifyMsgSig = HttpUtils.ParseUrl("msg_signature");
	string sVerifyMsgSig = "5c45ff5e21c57e6ad56bac8758b79b1d9ac89fd3";
	// string sVerifyTimeStamp = HttpUtils.ParseUrl("timestamp");
	string sVerifyTimeStamp = "1409659589";
	// string sVerifyNonce = HttpUtils.ParseUrl("nonce");
	string sVerifyNonce = "263014780";
	// string sVerifyEchoStr = HttpUtils.ParseUrl("echostr");
	string sVerifyEchoStr = "P9nAzCzyDtyTWESHep1vC5X9xho/qYX3Zpb4yKa9SKld1DsH3Iyt3tP3zNdtp+4RPcs8TgAE7OaBO+FZXvnaqQ==";
	int ret = 0;
	// ��Ҫ���ص�����
	string sEchoStr;
	ret = wxcpt.VerifyURL(sVerifyMsgSig, sVerifyTimeStamp, sVerifyNonce, sVerifyEchoStr, sEchoStr);
	if( ret!=0 )
	{
		cout<<"ERR: VerifyURL ret: "<< ret << endl;
		return ret;
	}
	// ret==0 ��ʾ��֤URL�ɹ�����Ҫ��sEchoStr���ظ���ҵ΢��
	// HttpUtils.SetResponse( sEchoStr );
	

	/*
	------------ʹ��ʾ���������û��ظ�����Ϣ����---------------
	�û��ظ���Ϣ���ߵ���¼���Ӧʱ����ҵ���յ��ص���Ϣ������Ϣ�Ǿ�����ҵ΢�ż���֮���������post��ʽ���͸���ҵ�����ĸ�ʽ��ο��ٷ��ĵ�
	������ҵ�յ���ҵ΢�ŵĻص���Ϣ���£�
	POST /cgi-bin/wxpush? msg_signature=477715d11cdb4164915debcba66cb864d751f3e6&timestamp=1409659813&nonce=1372623149 HTTP/1.1
	Host: qy.weixin.qq.com
	Content-Length: 613
	<xml>	<ToUserName><![CDATA[wx5823bf96d3bd56c7]]></ToUserName><Encrypt><![CDATA[RypEvHKD8QQKFhvQ6QleEB4J58tiPdvo+rtK1I9qca6aM/wvqnLSV5zEPeusUiX5L5X/0lWfrf0QADHHhGd3QczcdCUpj911L3vg3W/sYYvuJTs3TUUkSUXxaccAS0qhxchrRYt66wiSpGLYL42aM6A8dTT+6k4aSknmPj48kzJs8qLjvd4Xgpue06DOdnLxAUHzM6+kDZ+HMZfJYuR+LtwGc2hgf5gsijff0ekUNXZiqATP7PF5mZxZ3Izoun1s4zG4LUMnvw2r+KqCKIw+3IQH03v+BCA9nMELNqbSf6tiWSrXJB3LAVGUcallcrw8V2t9EL4EhzJWrQUax5wLVMNS0+rUPA3k22Ncx4XXZS9o0MBH27Bo6BpNelZpS+/uh9KsNlY6bHCmJU9p8g7m3fVKn28H3KDYA5Pl/T8Z1ptDAVe0lXdQ2YoyyH2uyPIGHBZZIs2pDBS8R07+qN+E7Q==]]></Encrypt>
	<AgentID><![CDATA[218]]></AgentID>
	</xml>

	��ҵ�յ�post����֮��Ӧ��	1.������url�ϵĲ�����������Ϣ��ǩ��(msg_signature)��ʱ���(timestamp)�Լ�������ִ�(nonce)
	2.��֤��Ϣ��ǩ������ȷ�ԡ�	3.��post��������ݽ���xml����������<Encrypt>��ǩ�����ݽ��н��ܣ����ܳ��������ļ����û��ظ���Ϣ�����ģ����ĸ�ʽ��ο��ٷ��ĵ�
	��2��3����������ҵ΢���ṩ�Ŀ⺯��DecryptMsg��ʵ�֡�
	*/
	
	// string sReqMsgSig = HttpUtils.ParseUrl("msg_signature");
	string sReqMsgSig = "477715d11cdb4164915debcba66cb864d751f3e6";
	// string sReqTimeStamp = HttpUtils.ParseUrl("timestamp");
	string sReqTimeStamp = "1409659813";
	// string sReqNonce = HttpUtils.ParseUrl("nonce");
	string sReqNonce = "1372623149";
	// post�������������
	string sReqData = 	"<xml><ToUserName><![CDATA[wx5823bf96d3bd56c7]]></ToUserName><Encrypt><![CDATA[RypEvHKD8QQKFhvQ6QleEB4J58tiPdvo+rtK1I9qca6aM/wvqnLSV5zEPeusUiX5L5X/0lWfrf0QADHHhGd3QczcdCUpj911L3vg3W/sYYvuJTs3TUUkSUXxaccAS0qhxchrRYt66wiSpGLYL42aM6A8dTT+6k4aSknmPj48kzJs8qLjvd4Xgpue06DOdnLxAUHzM6+kDZ+HMZfJYuR+LtwGc2hgf5gsijff0ekUNXZiqATP7PF5mZxZ3Izoun1s4zG4LUMnvw2r+KqCKIw+3IQH03v+BCA9nMELNqbSf6tiWSrXJB3LAVGUcallcrw8V2t9EL4EhzJWrQUax5wLVMNS0+rUPA3k22Ncx4XXZS9o0MBH27Bo6BpNelZpS+/uh9KsNlY6bHCmJU9p8g7m3fVKn28H3KDYA5Pl/T8Z1ptDAVe0lXdQ2YoyyH2uyPIGHBZZIs2pDBS8R07+qN+E7Q==]]></Encrypt><AgentID><![CDATA[218]]></AgentID></xml>";
	string sMsg;  // ����֮�������
	ret = wxcpt.DecryptMsg(sReqMsgSig, sReqTimeStamp, sReqNonce, sReqData, sMsg);
	if( ret!=0 )
	{
		cout << "ERR: DecryptMsg ret: " << ret << endl;
		return ret;
	}
	// ���ܳɹ���sMsg��Ϊxml��ʽ������
	// TODO: �����ĵĴ���
	// For example:
	string content;
	if( 0!= wxcpt.GetXmlField(sMsg, "Content", content) )
    {
		cout<<"Post data Format ERR"<<endl;
        return WXBizMsgCrypt_ParseXml_Error;
    }
	cout<<"content: "<<content<<endl;
	// ...
	// ...
	// ...
	
	
	/*
	------------ʹ��ʾ��������ҵ�ظ��û���Ϣ�ļ���---------------
	��ҵ�����ظ��û�����ϢҲ��Ҫ���м��ܣ�����ƴ�ӳ����ĸ�ʽ��xml����
	������ҵ��Ҫ�ظ��û����������£�
	<xml>
	<ToUserName><![CDATA[mycreate]]></ToUserName>
	<FromUserName><![CDATA[wx5823bf96d3bd56c7]]></FromUserName>
	<CreateTime>1348831860</CreateTime>
	<MsgType><![CDATA[text]]></MsgType>
	<Content><![CDATA[this is a test]]></Content>
	<MsgId>1234567890123456</MsgId>
	<AgentID>128</AgentID>
	</xml>

	Ϊ�˽��˶����Ļظ����û�����ҵӦ��	1.�Լ�����ʱ��ʱ���(timestamp),������ִ�(nonce)�Ա�������Ϣ��ǩ����Ҳ����ֱ���ô���ҵ΢�ŵ�post url�Ͻ������Ķ�Ӧֵ��
	2.�����ļ��ܵõ����ġ�
	3.�����ģ�����1���ɵ�timestamp,nonce����ҵ����ҵ΢���趨��token������Ϣ��ǩ����
	4.�����ģ���Ϣ��ǩ����ʱ�����������ִ�ƴ�ӳ�xml��ʽ���ַ��������͸���ҵ�š�
	����2��3��4����������ҵ΢���ṩ�Ŀ⺯��EncryptMsg��ʵ�֡�
	*/
	//��Ҫ���͵�����ΪsRespData
	string sRespData = "<xml><ToUserName><![CDATA[mycreate]]></ToUserName><FromUserName><![CDATA[wx5823bf96d3bd56c7]]></FromUserName><CreateTime>1348831860</CreateTime><MsgType><![CDATA[text]]></MsgType><Content><![CDATA[this is a test]]></Content><MsgId>1234567890123456</MsgId><AgentID>128</AgentID></xml>";
	string sEncryptMsg; 
	ret = wxcpt.EncryptMsg(sRespData, sReqTimeStamp, sReqNonce, sEncryptMsg);
	if( ret!=0 )
	{
		cout<<"ERR: EncryptMsg ret: "<<ret<<endl;
		return ret;
	}
	//TODO:
	// ret==0��ʾ���ܳɹ�����ҵ��Ҫ��sEncryptMsg����
	// HttpUtils.SetResponse(sEncryptMsg);
	cout<<sEncryptMsg<<endl;

    return 0;
}
