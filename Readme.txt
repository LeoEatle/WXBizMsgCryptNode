注意事项
1.WXBizMsgCrypt.h声明了WXBizMsgCrypt类，提供用户接入企业微信的三个接口。WXBizMsgCrypt.cpp文件提供了三个接口的实现。Sample.cpp文件提供了如何使用这三个接口的示例。
2.WXBizMsgCrypt类封装了VerifyURL, DecryptMsg, EncryptMsg三个接口，分别用于开发者验证回调url，收到用户回复消息的解密以及开发者回复消息的加密过程。使用方法可以参考Sample.cpp文件。
3.加解密协议请参考企业微信官方文档。
4.加解密过程使用了开源的openssl和tinyxml2库，请开发者自行安装之后使用。
  *openssl的版本号是openssl-1.0.1h，http://www.openssl.org/
  *tinyxml2的版本号是tinyxml2-2.1.0，https://github.com/leethomason/tinyxml2 