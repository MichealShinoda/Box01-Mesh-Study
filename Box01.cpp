// Source
void DumpMeshData() 
{
	INode* node = Core->GetSelNode(0); if (!node) {return; }
	TimeValue t = GetCOREInterface()->GetTime();
	Object* obj = node->EvalWorldState(t).obj;

	if (obj->CanConvertToType(triobjectCID))
	{
		// Get TriObject
		TriObject* tobj = (TriObject*)obj->ConvertToType(t, triobjectCID); if (!tobj) { return; }

		// Get Mesh
		Mesh mesh = tobj->GetMesh();

		// Compute Normals
		MeshNormalSpec* mesh_ns = mesh.GetSpecifiedNormals();
		Point3* mesh_n = mesh_ns->GetNormalArray();

		// Get Mesh Data Sizes
		int vNum = mesh.numVerts;
		int nNum = mesh_ns->GetNumNormals();
		int fNum = mesh.numFaces;
		int tNum = mesh.numTVerts;

		mprintf(L"Object [%s] Data\n", node->GetName());
		mprintf(L"======================\n");

		for (size_t i = 0; i < vNum; i++)
		{
			mprintf(L"Vert[%d] = %f %f %f\n", i,
				mesh.verts[i].x,
				mesh.verts[i].y,
				mesh.verts[i].z);
		}
		mprintf(L"======================\n");

		for (size_t i = 0; i < nNum; i++)
		{
			mprintf(L"Normal[%d] = %f %f %f\n", i,
				mesh_n[i].x,
				mesh_n[i].y,
				mesh_n[i].z);
		}
		mprintf(L"======================\n");

		for (size_t i = 0; i < tNum; i++)
		{
			mprintf(L"UV[%d] = %f %f %f\n", i,
				mesh.tVerts[i].x,
				mesh.tVerts[i].y,
				mesh.tVerts[i].z);
		}
		mprintf(L"======================\n");

		for (size_t i = 0; i < fNum; i++)
		{
			Face face = mesh.faces[i];
			TVFace tface = mesh.tvFace[i];
			for (size_t j = 0; j < 3; j++)
			{
				mprintf(L"Face[%d] Vert[%d] = Vert ID :%d / Normal ID :%d / UV ID : %d / MTL ID : %d\n", i, j,
					face.v[j],
					mesh_ns->GetNormalIndex(i, j),
					tface.t[j],
					face.getMatID());
			}
		}
	}
}

/* Result :

Object [Box001] Data
======================
Vert[0] = -5.000000 -5.000000 -5.000000
Vert[1] = 5.000000 -5.000000 -5.000000
Vert[2] = -5.000000 5.000000 -5.000000
Vert[3] = 5.000000 5.000000 -5.000000
Vert[4] = -5.000000 -5.000000 5.000000
Vert[5] = 5.000000 -5.000000 5.000000
Vert[6] = -5.000000 5.000000 5.000000
Vert[7] = 5.000000 5.000000 5.000000
======================
Normal[0] = 0.000000 0.000000 -1.000000
Normal[1] = 0.000000 0.000000 -1.000000
Normal[2] = 0.000000 0.000000 -1.000000
Normal[3] = 0.000000 0.000000 -1.000000
Normal[4] = 0.000000 0.000000 1.000000
Normal[5] = 0.000000 0.000000 1.000000
Normal[6] = 0.000000 0.000000 1.000000
Normal[7] = 0.000000 0.000000 1.000000
Normal[8] = 0.000000 -1.000000 0.000000
Normal[9] = 0.000000 -1.000000 0.000000
Normal[10] = 0.000000 -1.000000 0.000000
Normal[11] = 0.000000 -1.000000 0.000000
Normal[12] = 1.000000 0.000000 0.000000
Normal[13] = 1.000000 0.000000 0.000000
Normal[14] = 1.000000 0.000000 0.000000
Normal[15] = 1.000000 0.000000 0.000000
Normal[16] = 0.000000 1.000000 0.000000
Normal[17] = 0.000000 1.000000 0.000000
Normal[18] = 0.000000 1.000000 0.000000
Normal[19] = 0.000000 1.000000 0.000000
Normal[20] = -1.000000 0.000000 0.000000
Normal[21] = -1.000000 0.000000 0.000000
Normal[22] = -1.000000 0.000000 0.000000
Normal[23] = -1.000000 0.000000 0.000000
======================
UV[0] = 1.000000 0.000000 0.000000
UV[1] = 0.000000 0.000000 0.000000
UV[2] = 1.000000 1.000000 0.000000
UV[3] = 0.000000 1.000000 0.000000
UV[4] = 0.000000 0.000000 0.000000
UV[5] = 1.000000 0.000000 0.000000
UV[6] = 0.000000 1.000000 0.000000
UV[7] = 1.000000 1.000000 0.000000
UV[8] = 0.000000 0.000000 0.000000
UV[9] = 1.000000 0.000000 0.000000
UV[10] = 0.000000 1.000000 0.000000
UV[11] = 1.000000 1.000000 0.000000
UV[12] = 0.000000 0.000000 0.000000
UV[13] = 1.000000 0.000000 0.000000
UV[14] = 0.000000 1.000000 0.000000
UV[15] = 1.000000 1.000000 0.000000
UV[16] = 0.000000 0.000000 0.000000
UV[17] = 1.000000 0.000000 0.000000
UV[18] = 0.000000 1.000000 0.000000
UV[19] = 1.000000 1.000000 0.000000
UV[20] = 0.000000 0.000000 0.000000
UV[21] = 1.000000 0.000000 0.000000
UV[22] = 0.000000 1.000000 0.000000
UV[23] = 1.000000 1.000000 0.000000
======================
Face[0] Vert[0] = Vert ID :0 / Normal ID :0 / UV ID : 0 / MTL ID : 60
Face[0] Vert[1] = Vert ID :2 / Normal ID :1 / UV ID : 2 / MTL ID : 60
Face[0] Vert[2] = Vert ID :3 / Normal ID :2 / UV ID : 3 / MTL ID : 60
Face[1] Vert[0] = Vert ID :3 / Normal ID :2 / UV ID : 3 / MTL ID : 60
Face[1] Vert[1] = Vert ID :1 / Normal ID :3 / UV ID : 1 / MTL ID : 60
Face[1] Vert[2] = Vert ID :0 / Normal ID :0 / UV ID : 0 / MTL ID : 60
Face[2] Vert[0] = Vert ID :4 / Normal ID :4 / UV ID : 4 / MTL ID : 60
Face[2] Vert[1] = Vert ID :5 / Normal ID :5 / UV ID : 5 / MTL ID : 60
Face[2] Vert[2] = Vert ID :7 / Normal ID :6 / UV ID : 7 / MTL ID : 60
Face[3] Vert[0] = Vert ID :7 / Normal ID :6 / UV ID : 7 / MTL ID : 60
Face[3] Vert[1] = Vert ID :6 / Normal ID :7 / UV ID : 6 / MTL ID : 60
Face[3] Vert[2] = Vert ID :4 / Normal ID :4 / UV ID : 4 / MTL ID : 60
Face[4] Vert[0] = Vert ID :0 / Normal ID :8 / UV ID : 8 / MTL ID : 23
Face[4] Vert[1] = Vert ID :1 / Normal ID :9 / UV ID : 9 / MTL ID : 23
Face[4] Vert[2] = Vert ID :5 / Normal ID :10 / UV ID : 11 / MTL ID : 23
Face[5] Vert[0] = Vert ID :5 / Normal ID :10 / UV ID : 11 / MTL ID : 23
Face[5] Vert[1] = Vert ID :4 / Normal ID :11 / UV ID : 10 / MTL ID : 23
Face[5] Vert[2] = Vert ID :0 / Normal ID :8 / UV ID : 8 / MTL ID : 23
Face[6] Vert[0] = Vert ID :1 / Normal ID :12 / UV ID : 12 / MTL ID : 2
Face[6] Vert[1] = Vert ID :3 / Normal ID :13 / UV ID : 13 / MTL ID : 2
Face[6] Vert[2] = Vert ID :7 / Normal ID :14 / UV ID : 15 / MTL ID : 2
Face[7] Vert[0] = Vert ID :7 / Normal ID :14 / UV ID : 15 / MTL ID : 2
Face[7] Vert[1] = Vert ID :5 / Normal ID :15 / UV ID : 14 / MTL ID : 2
Face[7] Vert[2] = Vert ID :1 / Normal ID :12 / UV ID : 12 / MTL ID : 2
Face[8] Vert[0] = Vert ID :3 / Normal ID :16 / UV ID : 16 / MTL ID : 23
Face[8] Vert[1] = Vert ID :2 / Normal ID :17 / UV ID : 17 / MTL ID : 23
Face[8] Vert[2] = Vert ID :6 / Normal ID :18 / UV ID : 19 / MTL ID : 23
Face[9] Vert[0] = Vert ID :6 / Normal ID :18 / UV ID : 19 / MTL ID : 23
Face[9] Vert[1] = Vert ID :7 / Normal ID :19 / UV ID : 18 / MTL ID : 23
Face[9] Vert[2] = Vert ID :3 / Normal ID :16 / UV ID : 16 / MTL ID : 23
Face[10] Vert[0] = Vert ID :2 / Normal ID :20 / UV ID : 20 / MTL ID : 2
Face[10] Vert[1] = Vert ID :0 / Normal ID :21 / UV ID : 21 / MTL ID : 2
Face[10] Vert[2] = Vert ID :4 / Normal ID :22 / UV ID : 23 / MTL ID : 2
Face[11] Vert[0] = Vert ID :4 / Normal ID :22 / UV ID : 23 / MTL ID : 2
Face[11] Vert[1] = Vert ID :6 / Normal ID :23 / UV ID : 22 / MTL ID : 2
Face[11] Vert[2] = Vert ID :2 / Normal ID :20 / UV ID : 20 / MTL ID : 2*/