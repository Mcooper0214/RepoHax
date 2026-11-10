    static void SpawnItem(Item item)
    {
        Unity::Camera camera = SemiFunc::MainCamera();
        if (!camera)
            return;

        if (!item)
            return;

        auto prefab = item.prefab();

        Unity::Transform transform = camera.GetTransform();
        Unity::Vector3 pos = transform.GetPosition() + transform.GetForward() * 2.f - transform.GetUp();

        // Mutually exclusive: in single-player both predicates were true,
        // firing PhotonNetwork.Instantiate with no Photon room (crash),
        // then also spawning a local copy.
        if (!SemiFunc::IsMultiplayer())
            Unity::Object::Instantiate<Unity::GameObject>(prefab.Prefab(), pos, Unity::Quaternion::identity());
        else if (SemiFunc::IsMasterClient())
            Photon::PhotonNetwork::InstantiateRoomObject(prefab.resourcePath(), pos, Unity::Quaternion::identity());
    }
