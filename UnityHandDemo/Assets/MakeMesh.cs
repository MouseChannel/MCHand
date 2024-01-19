using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MakeMesh : MonoBehaviour
{
    private MeshFilter meshFilter;
    private Mesh mesh;
    public bool is_left = false;

    void Start()
    {
        // 创建MeshFilter和MeshRenderer组件
        meshFilter = GetComponent<MeshFilter>();
        mesh = new Mesh();
        // MeshRenderer meshRenderer = gameObject.AddComponent<MeshRenderer>();
        //
        // // 创建Mesh对象
        //
        //
        // // 顶点坐标
        // Vector3[] vertices = new Vector3[]
        // {
        //     new Vector3(-1f, -1f, 0f),
        //     new Vector3(1f, -1f, 0f),
        //     new Vector3(1f, 1f, 0f),
        //     new Vector3(-1f, 1f, 0f)
        // };
        //
        // // 三角形顶点索引
        // int[] triangles = new int[] { 0, 1, 2, 0, 2, 3 };
        //
        // // UV坐标
        // // Vector2[] uv = new Vector2[]
        // // {
        // //     new Vector2(0f, 0f),
        // //     new Vector2(1f, 0f),
        // //     new Vector2(1f, 1f),
        // //     new Vector2(0f, 1f)
        // // };
        //
        // // 设置Mesh的顶点、三角形和UV
        // mesh.vertices = vertices;
        // mesh.triangles = triangles;
        // // mesh.uv = uv;
        //
        // // 计算法线和切线
        // mesh.RecalculateNormals();
        // mesh.RecalculateTangents();
        //
        // // 将Mesh赋给MeshFilter
        // meshFilter.mesh = mesh;
    }

    // Update is called once per frame
    void Update()
    {
        if (is_left)
        {
            mesh.vertices = MCHand.lvertices;
            mesh.triangles = MCHand.lface;
        }
        else
        {
            mesh.vertices = MCHand.rvertices;
            mesh.triangles = MCHand.rface;
        }

        mesh.RecalculateNormals();
        mesh.RecalculateTangents();

        // 将Mesh赋给MeshFilter
        meshFilter.mesh = mesh;
    }
}