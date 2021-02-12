// Source
using UnityEngine;
public class MeshDump : MonoBehaviour
{
    private MeshFilter meshFilter;
    private void DumpMeshData()
    {
        string dumpData = $"Mesh Dump [{this.name}]\n";

        dumpData += $"Vertex Data [{meshFilter.mesh.vertices.Length}] :\n";

        for (int i = 0; i < meshFilter.mesh.vertices.Length; i++)
        {
            var vert = meshFilter.mesh.vertices[i];
            dumpData += $"vert[{i}] = {vert.x} {vert.y} {vert.z}\n";
        }
        dumpData += "\n====================================\n";

        dumpData += $"Normal Data [{meshFilter.mesh.normals.Length}] :\n";

        for (int i = 0; i < meshFilter.mesh.normals.Length; i++)
        {
            var vert = meshFilter.mesh.normals[i];
            dumpData += $"normal[{i}] = {vert.x} {vert.y} {vert.z}\n";
        }
        dumpData += "\n====================================\n";

        dumpData += $"Normal Data [{meshFilter.mesh.uv.Length}] :\n";

        for (int i = 0; i < meshFilter.mesh.uv.Length; i++)
        {
            var vert = meshFilter.mesh.uv[i];
            dumpData += $"uv[{i}] = {vert.x} {vert.y}\n";
        }
        dumpData += "\n====================================\n";

        dumpData += $"Sub Mesh Data [{meshFilter.mesh.subMeshCount}] :\n";

        for (int i = 0; i < meshFilter.mesh.subMeshCount; i++)
        {
            var submesh = meshFilter.mesh.GetTriangles(i);
            dumpData += $"Submesh[{i}] Indices ({submesh.Length}) : \n";
            for (int j = 0; j < submesh.Length; j++)
            {
                var index = submesh[j];
                dumpData += $"index[{j}] = {index}\n";
            }
        }

        System.IO.File.WriteAllText($"{this.name}.txt", dumpData);
    }
    void Start()
    {
        meshFilter = this.GetComponent<MeshFilter>();
        DumpMeshData();
    }
}

/* Result :

Mesh Dump [Box001]
Vertex Data [24] :
vert[0] = 0.5 -0.5 0.5
vert[1] = -0.5 -0.5 -0.5
vert[2] = 0.5 -0.5 -0.5
vert[3] = -0.5 -0.5 0.5
vert[4] = 0.5 0.5 0.5
vert[5] = -0.5 0.5 -0.5
vert[6] = -0.5 0.5 0.5
vert[7] = 0.5 0.5 -0.5
vert[8] = 0.5 -0.5 0.5
vert[9] = -0.5 0.5 0.5
vert[10] = -0.5 -0.5 0.5
vert[11] = 0.5 0.5 0.5
vert[12] = -0.5 -0.5 0.5
vert[13] = -0.5 0.5 -0.5
vert[14] = -0.5 -0.5 -0.5
vert[15] = -0.5 0.5 0.5
vert[16] = -0.5 -0.5 -0.5
vert[17] = 0.5 0.5 -0.5
vert[18] = 0.5 -0.5 -0.5
vert[19] = -0.5 0.5 -0.5
vert[20] = 0.5 -0.5 -0.5
vert[21] = 0.5 0.5 0.5
vert[22] = 0.5 -0.5 0.5
vert[23] = 0.5 0.5 -0.5

====================================
Normal Data [24] :
normal[0] = 0 -1 0
normal[1] = 0 -1 0
normal[2] = 0 -1 0
normal[3] = 0 -1 0
normal[4] = 0 1 0
normal[5] = 0 1 0
normal[6] = 0 1 0
normal[7] = 0 1 0
normal[8] = 0 0 1
normal[9] = 0 0 1
normal[10] = 0 0 1
normal[11] = 0 0 1
normal[12] = -1 0 0
normal[13] = -1 0 0
normal[14] = -1 0 0
normal[15] = -1 0 0
normal[16] = 0 0 -1
normal[17] = 0 0 -1
normal[18] = 0 0 -1
normal[19] = 0 0 -1
normal[20] = 1 0 0
normal[21] = 1 0 0
normal[22] = 1 0 0
normal[23] = 1 0 0

====================================
Normal Data [24] :
uv[0] = 1 0
uv[1] = 0 1
uv[2] = 1 1
uv[3] = 0 0
uv[4] = 0 0
uv[5] = 1 1
uv[6] = 1 0
uv[7] = 0 1
uv[8] = 0 0
uv[9] = 1 1
uv[10] = 1 0
uv[11] = 0 1
uv[12] = 0 0
uv[13] = 1 1
uv[14] = 1 0
uv[15] = 0 1
uv[16] = 0 0
uv[17] = 1 1
uv[18] = 1 0
uv[19] = 0 1
uv[20] = 0 0
uv[21] = 1 1
uv[22] = 1 0
uv[23] = 0 1

====================================
Sub Mesh Data [1] :
Submesh[0] Indices (36) : 
index[0] = 0
index[1] = 1
index[2] = 2
index[3] = 1
index[4] = 0
index[5] = 3
index[6] = 4
index[7] = 5
index[8] = 6
index[9] = 5
index[10] = 4
index[11] = 7
index[12] = 8
index[13] = 9
index[14] = 10
index[15] = 9
index[16] = 8
index[17] = 11
index[18] = 12
index[19] = 13
index[20] = 14
index[21] = 13
index[22] = 12
index[23] = 15
index[24] = 16
index[25] = 17
index[26] = 18
index[27] = 17
index[28] = 16
index[29] = 19
index[30] = 20
index[31] = 21
index[32] = 22
index[33] = 21
index[34] = 20
index[35] = 23*/