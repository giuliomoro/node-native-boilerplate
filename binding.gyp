{
    "targets": [
        {
            "target_name": "NativeExtension",
            "sources": [ "NativeExtension.cc", "functions.cc", "render.cpp", "default_main.cpp"],
            "include_dirs" : [
 	 			"<!(node -e \"require('nan')\")",
				"/root/Bela/include/",
				"/usr/xenomai/include",
			],
			'library_dirs': [
				'/root/Bela/lib',
				"/usr/xenomai/lib",
			],
			'link_settings': {
				'libraries': [
					'-lbela',
					'-lrt',
					'-lnative',
					'-lxenomai',
					'-lsndfile',
					'-lasound',
				],
			},
        }
    ],
}
