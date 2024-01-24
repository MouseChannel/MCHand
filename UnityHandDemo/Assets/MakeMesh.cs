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
         
        meshFilter = GetComponent<MeshFilter>();
        mesh = new Mesh();
        
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

    
        meshFilter.mesh = mesh;
    }
}