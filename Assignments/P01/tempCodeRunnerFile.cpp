 bstMapString["last_name"].insert(data.last_name, data);
        // BST for email
        bstMapString["email"].insert(data.email, data);
        // BST for car_model
        bstMapString["car_model"].insert(data.car_model, data);
        // BST for job_title
        bstMapString["job_title"].insert(data.job_title, data);
        // BST for address
        bstMapString["address"].insert(data.address, data);
        // BST for phone_number
        bstMapString["phone_number"].insert(data.phone_number, data);
        // BST for latitude
        bstMapDouble["latitude"].insert(data.latitude, data);
        // BST for GPS
        bstMapGPS["GPS"].insert(data.gps, data);
        // insert JsonData in linked_list
        l.add(new JsonData(data));