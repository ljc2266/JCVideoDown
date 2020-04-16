	有时候需要做个PPT需要一些视频素材，或者从某些网站观看一些无网页广告的视频，然而这些视频本身嵌入到网页中，为了方便从网页中导出视频，做了一个下载工具。首先上图展示效果：
  
![Image text](https://raw.githubusercontent.com/ljc2266/JCVideoDown/master/show.png)
   
这里对里面使用的知识点进行说明：
1.	使用CHttpConnection相关http操作的方式进行原始网页的代码下载并初步解析。
2.	为解决有些网站通过js动态加载视频，使用WebBrowser进行网页动态加载，并使用IHTMLDocument2进行源码解析。
3.	采用策略模式对html <video><object><embed>进行解析，目前还不支持flash，可以扩展flash。
4.	使用JCThreadManager进行多线程管理，可以在作者这里找到开源代码。
5.	使用MD5对原始url加密作为tag，并支持断点续传。
扩展格式：
如果需要扩展其他格式可以继承CJCVideoStrategy，实现接口方法vector<CString> GetVideoUrls(CString strUrlCode);并且把类名加入到CJCVideoDownDlg下面的STARTVIDEOFORMAT和ENDVIDEOFORMAT之间。
 
目前只支持<video> <object> <embed>比如增加CJCFlashFormat可以使用ADDVIDEOFORMAT(CJCFlashFormat)添加到STARTVIDEOFORMAT和ENDVIDEOFORMAT中间。
