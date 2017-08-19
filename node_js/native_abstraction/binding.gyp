{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "native_addon",
      "sources": [ "main.cpp" ]
    }
  ]
}
