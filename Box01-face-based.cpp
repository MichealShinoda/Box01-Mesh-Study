//Source
#define CURRENT				0
#define NEXT				1
#define NEXTNEXT			2
Point3 toRightHanded(Point3& input){return Point3(-input.x * 0.1f, input.z * 0.1f, -input.y * 0.1f);}
void DumpMeshDataFaceBased()
{
	INode* node = Core->GetSelNode(0); if (!node) { return; }
	TimeValue t = GetCOREInterface()->GetTime();
	Object* obj = node->EvalWorldState(t).obj;

	if (obj->CanConvertToType(triobjectCID))
	{
		TriObject* tobj = (TriObject*)obj->ConvertToType(t, triobjectCID); if (!tobj) { return; }
		Mesh mesh = tobj->GetMesh();
		MeshNormalSpec* mesh_ns = mesh.GetSpecifiedNormals();
		Point3* mesh_n = mesh_ns->GetNormalArray();

		// Get Mesh Data Sizes
		int vNum = mesh.numVerts;
		int nNum = mesh_ns->GetNumNormals();
		int fNum = mesh.numFaces;
		int fNumLinear = fNum * 3;
		int tNum = mesh.numTVerts;

		mprintf(L"Object [%s] Data [ Face Based ]:\n", node->GetName());
		mprintf(L"======================\n");

		Point3* vbuff = (Point3*)malloc(fNumLinear * sizeof(Point3));
		Point3* nbuff = (Point3*)malloc(fNumLinear * sizeof(Point3));
		int* fbuff = (int*)malloc(fNumLinear * sizeof(int));
		Point2* uvbuff = (Point2*)malloc(fNumLinear * sizeof(Point2));

		// Copying Mesh Data
		for (size_t i = 0; i < fNum; i++) {

			Face* getface = &mesh.faces[i];
			TVFace* gettexface = &mesh.tvFace[i];

			// Update Vertex Buffer
			if (vNum != 0) vbuff[i*3 + CURRENT]		= toRightHanded(mesh.verts[getface->v[CURRENT]]);
			if (vNum != 0) vbuff[i*3 + NEXT]		= toRightHanded(mesh.verts[getface->v[NEXT]]);
			if (vNum != 0) vbuff[i*3 + NEXTNEXT]	= toRightHanded(mesh.verts[getface->v[NEXTNEXT]]);

			// Update Normal Buffer
			if (nNum != 0) nbuff[i*3 + CURRENT] =
				toRightHanded(mesh_n[mesh_ns->GetNormalIndex(i, CURRENT)]);
			if (nNum != 0) nbuff[i*3 + NEXT] =
				toRightHanded(mesh_n[mesh_ns->GetNormalIndex(i, NEXT)]);
			if (nNum != 0) nbuff[i*3 + NEXTNEXT] =
				toRightHanded(mesh_n[mesh_ns->GetNormalIndex(i, NEXTNEXT)]);

			// Update UV Buffer
			if (tNum != 0) uvbuff[i*3 + CURRENT] = Point2(mesh.tVerts[gettexface->t[CURRENT]].x,
				mesh.tVerts[gettexface->t[CURRENT]].y);
			if (tNum != 0) uvbuff[i*3 + NEXT] = Point2(mesh.tVerts[gettexface->t[NEXT]].x,
				mesh.tVerts[gettexface->t[NEXT]].y);
			if (tNum != 0) uvbuff[i*3 + NEXTNEXT] = Point2(mesh.tVerts[gettexface->t[NEXTNEXT]].x,
				mesh.tVerts[gettexface->t[NEXTNEXT]].y);

			// Update Face Buffer ( Indices )
			fbuff[i*3 + CURRENT] = (fNumLinear - (i*3 + CURRENT)) - 1;
			fbuff[i*3 + NEXT] = (fNumLinear - (i*3 + NEXT)) - 1;
			fbuff[i*3 + NEXTNEXT] = (fNumLinear - (i*3 + NEXTNEXT)) - 1;
		}

		// Dumping Data
		for (size_t i = 0; i < fNumLinear; i++)
			mprintf(L"Vert[%d] = %f %f %f\n", i,
				vbuff[i].x,
				vbuff[i].y,
				vbuff[i].z);
		mprintf(L"======================\n");

		for (size_t i = 0; i < fNumLinear; i++)
			mprintf(L"Normal[%d] = %f %f %f\n", i,
				nbuff[i].x,
				nbuff[i].y,
				nbuff[i].z);
		mprintf(L"======================\n");

		for (size_t i = 0; i < fNumLinear; i++)
			mprintf(L"UV[%d] = %f %f\n", i,
				uvbuff[i].x, uvbuff[i].y);
		mprintf(L"======================\n");
		
		for (size_t i = 0; i < fNumLinear; i++)
			mprintf(L"Indice[%d] = %d\n", i,fbuff[i]);

		// Release Resoruces
		free(vbuff); free(nbuff); free(fbuff); free(uvbuff);
	}
}

/* Result :

Object [Box001] Data [ Face Based ]:
======================
Vert[0] = 0.500000 -0.500000 0.500000
Vert[1] = 0.500000 -0.500000 -0.500000
Vert[2] = -0.500000 -0.500000 -0.500000
Vert[3] = -0.500000 -0.500000 -0.500000
Vert[4] = -0.500000 -0.500000 0.500000
Vert[5] = 0.500000 -0.500000 0.500000
Vert[6] = 0.500000 0.500000 0.500000
Vert[7] = -0.500000 0.500000 0.500000
Vert[8] = -0.500000 0.500000 -0.500000
Vert[9] = -0.500000 0.500000 -0.500000
Vert[10] = 0.500000 0.500000 -0.500000
Vert[11] = 0.500000 0.500000 0.500000
======================
Normal[0] = -0.000000 -0.100000 -0.000000
Normal[1] = -0.000000 -0.100000 -0.000000
Normal[2] = -0.000000 -0.100000 -0.000000
Normal[3] = -0.000000 -0.100000 -0.000000
Normal[4] = -0.000000 -0.100000 -0.000000
Normal[5] = -0.000000 -0.100000 -0.000000
Normal[6] = -0.000000 0.100000 -0.000000
Normal[7] = -0.000000 0.100000 -0.000000
Normal[8] = -0.000000 0.100000 -0.000000
Normal[9] = -0.000000 0.100000 -0.000000
Normal[10] = -0.000000 0.100000 -0.000000
Normal[11] = -0.000000 0.100000 -0.000000
======================
UV[0] = 1.000000 0.000000
UV[1] = 1.000000 1.000000
UV[2] = 0.000000 1.000000
UV[3] = 0.000000 1.000000
UV[4] = 0.000000 0.000000
UV[5] = 1.000000 0.000000
UV[6] = 0.000000 0.000000
UV[7] = 1.000000 0.000000
UV[8] = 1.000000 1.000000
UV[9] = 1.000000 1.000000
UV[10] = 0.000000 1.000000
UV[11] = 0.000000 0.000000
======================
Indice[0] = 35
Indice[1] = 34
Indice[2] = 33
Indice[3] = 32
Indice[4] = 31
Indice[5] = 30
Indice[6] = 29
Indice[7] = 28
Indice[8] = 27
Indice[9] = 26
Indice[10] = 25
Indice[11] = 24
Indice[12] = 23
Indice[13] = 22
Indice[14] = 21
Indice[15] = 20
Indice[16] = 19
Indice[17] = 18
Indice[18] = 17
Indice[19] = 16
Indice[20] = 15
Indice[21] = 14
Indice[22] = 13
Indice[23] = 12
Indice[24] = 11
Indice[25] = 10
Indice[26] = 9
Indice[27] = 8
Indice[28] = 7
Indice[29] = 6
Indice[30] = 5
Indice[31] = 4
Indice[32] = 3
Indice[33] = 2
Indice[34] = 1
Indice[35] = 0*/
