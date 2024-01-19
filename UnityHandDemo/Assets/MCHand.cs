using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnityEngine;
using System.Runtime.InteropServices;
using UnityEngine.UI;

public class MCHand : MonoBehaviour
{
    // Start is called before the first frame update
    [DllImport("libsrc.so")]
    public static extern void MCHand_Init(string path);


    [DllImport("libsrc.so")]
    public static extern void RegisterCallback(CallbackDelegate callback);


    [DllImport("libsrc.so")]
    public static extern void MCHand_NeedJoint();

    [DllImport("libsrc.so")]
    public static extern void MCHand_NeedMesh();

    [DllImport("libsrc.so")]
    // public static extern void MCHand_Infer(float[] input_img, int height, int width);
    public static extern IntPtr MCHand_Infer();

    [DllImport("libsrc.so")]
    public static extern IntPtr MCHand_GetLeftJoint();

    [DllImport("libsrc.so")]
    public static extern IntPtr MCHand_GetRightJoint();

    [DllImport("libsrc.so")]
    public static extern IntPtr MCHand_GetLeftMeshFace();

    [DllImport("libsrc.so")]
    public static extern IntPtr MCHand_GetRightMeshFace();

    [DllImport("libsrc.so")]
    public static extern IntPtr MCHand_GetLeftMesh();

    [DllImport("libsrc.so")]
    public static extern IntPtr MCHand_GetRightMesh();

    [DllImport("libsrc.so")]
    public static extern IntPtr MCHand_vis_joint();

    [DllImport("libsrc.so")]
    public static extern void OnlyTest();


    public delegate void CallbackDelegate(string message);

    private static void CSharpCallback(string message)
    {
        Debug.Log("mocheng Call: " + message);
    }


    public RawImage delete;
    Texture2D display;

    static public int[] lface = new int[4614];
    static public int[] rface = new int[4614];
    float[] lvert = new float[2334];
    float[] rvert = new float[2334];
    static public Vector3[] lvertices = new Vector3[778];
    static public Vector3[] rvertices = new Vector3[778];

    void Start()
    {
        display = new Texture2D(0, 0);
        // return;
        CallbackDelegate csharpCallback = new CallbackDelegate(CSharpCallback);

        RegisterCallback(csharpCallback);


        MCHand_Init("/home/mocheng/project/RECONSTRCUT/InterWild/demo/mochengres.onnx");
        GetFace();
        MCHand_NeedJoint();
        MCHand_NeedMesh();
    }

    void GetFace()
    {
        var lptr = MCHand_GetLeftMeshFace();
        Marshal.Copy(lptr, lface, 0, lface.Length);


        var rptr = MCHand_GetRightMeshFace();
        Marshal.Copy(rptr, rface, 0, rface.Length);
    }

    void Update()
    {
        // Debug.Log(123);
        var frame_size = MCHand_Infer();
        var frame_height = Marshal.ReadInt32(frame_size, 0);
        var frame_width = Marshal.ReadInt32(frame_size, sizeof(int));

        MCHand_GetLeftJoint();
        MCHand_GetRightJoint();
        var vis = MCHand_vis_joint();
        float[] vis_receive = new float[frame_height * frame_width * 3];
        Marshal.Copy(vis, vis_receive, 0, frame_height * frame_width * 3);
        Color32[] colors = new Color32[vis_receive.Length / 3]; // 4 channels (r, g, b, a) per element

        for (int i = 0; i < vis_receive.Length / 3; i++)
        {
            byte r = (byte)vis_receive[i * 3];

            byte g = (byte)vis_receive[i * 3 + 1];
            byte b = (byte)vis_receive[i * 3 + 2];
            // float a = floatArray[i * 4 + 3];

            colors[i] = new Color32(r, g, b, 255);
        }

        if (display.width != frame_height || display.height != frame_width)
        {
            display = new Texture2D(frame_height, frame_width);
        }

        display.SetPixels32(colors);
        display.Apply();


        delete.texture = display;


        var lptr = MCHand_GetLeftMesh();

        Marshal.Copy(lptr, lvert, 0, lvert.Length);


        var rptr = MCHand_GetRightMesh();
        Marshal.Copy(rptr, rvert, 0, rvert.Length);
        Handle_MeshData();
    }

    void Handle_MeshData()
    {
        for (int i = 0; i < lvertices.Length; i++)
        {
            lvertices[i][0] = lvert[i * 3]  ;
            lvertices[i][1] = lvert[i * 3 + 1]  ;
            lvertices[i][2] = lvert[i * 3 + 2]  ;
            rvertices[i][0] = rvert[i * 3]  ;
            rvertices[i][1] = rvert[i * 3 + 1]  ;
            rvertices[i][2] = rvert[i * 3 + 2]  ;
        }
    }


    // Update is called once per frame
}