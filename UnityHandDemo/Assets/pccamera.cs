using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class pccamera : MonoBehaviour
{
    public RawImage rawImage;  
 
    private WebCamTexture webCamTexture;

    void Start()
    {
        webCamTexture = new WebCamTexture();
        
        rawImage.texture = webCamTexture;
       
        webCamTexture.Play();
   
    }

 
    public void ToOpenCamera()
    {
        StartCoroutine("OpenCamera");
    }

    public IEnumerator OpenCamera()
    {
        int maxl = Screen.width;
        if (Screen.height > Screen.width)
        {
            maxl = Screen.height;
        }

   
        yield return Application.RequestUserAuthorization(UserAuthorization.WebCam);
        if (Application.HasUserAuthorization(UserAuthorization.WebCam))
        {
            if (webCamTexture != null)
            {
                webCamTexture.Stop();
            }
 
            if (rawImage != null)
            {
                rawImage.gameObject.SetActive(true);
            }

            
            int i = 0;
            while (WebCamTexture.devices.Length <= 0 && i < 300)
            {
                yield return new WaitForEndOfFrame();
                i++;
            }

            WebCamDevice[] devices = WebCamTexture.devices; //获取可用设备
            if (WebCamTexture.devices.Length <= 0)
            {
                Debug.LogError("没有摄像头设备，请检查");
            }
            else
            {
                string devicename = devices[0].name;
                
                webCamTexture = new WebCamTexture();

                
                if (rawImage != null)
                {
                    rawImage.texture = webCamTexture;
                }

               
                webCamTexture.Play();
            }
        }
        else
        {
            Debug.LogError("error");
        }
    }

    private void OnApplicationPause(bool pause)
    {
   
        if (webCamTexture != null)
        {
            if (pause)
            {
                webCamTexture.Pause();
            }
            else
            {
                webCamTexture.Play();
            }
        }
    }


    private void OnDestroy()
    {
        if (webCamTexture != null)
        {
            webCamTexture.Stop();
        }
    }
}