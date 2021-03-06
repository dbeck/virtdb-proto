{
    'target_defaults': {
        'default_configuration': 'Debug',
        'configurations': {
            'Debug': { 'defines': ['DEBUG', '_DEBUG', ], },
            'Release': { 'defines': ['NDEBUG', 'RELEASE', ], },
        },
        'include_dirs': [
            '<!(pwd)',
            './',
            '/usr/local/include/',
            '/usr/include/',
            '<!@(pkg-config --variable=includedir protobuf)',
        ],
        'cflags': [
            '-std=c++11',
            '-Wall',
        ],
        'defines': [
            'PIC',
            'STD_CXX_11',
            '_THREAD_SAFE',
        ],
        'target_conditions': [
            ['_type=="shared_library"', {'cflags': ['-fPIC']}],
            ['_type=="static_library"', {'cflags': ['-fPIC']}],
            ['_type=="executable"',     {'cflags': ['-fPIC']}],
        ],
        'conditions': [
            ['OS=="mac"', {
                'cflags':                        [ '<!@(pkg-config --cflags protobuf)', '-std=c++11', '-I<!(pwd)/', ],
                'xcode_settings':  {
                    'GCC_ENABLE_CPP_EXCEPTIONS':   'YES',
                    'OTHER_LDFLAGS':               [ '<!@(pkg-config --libs-only-L --libs-only-l protobuf)' ],
                    'OTHER_CFLAGS':                [ '-std=c++11', '-I<!(pwd)/', '-I<!(pwd)/cppzmq/' ],
                },
                'targets': {
                    'target_name':       'env_echo',
                    'type':              'none',
                    'sources':           [ '', ],
                    'actions': [{
                        'action_name':   'echo_env_Variables',
                        'inputs':        [ '', ],
                        'outputs':       [ '', ],
                        'action':        [ 'env' ],
                    },]
                }
            },],
            ['OS=="linux"', {
                'cflags':                        [ '<!@(pkg-config --cflags protobuf)' ],
                'variables': {
                    'proto_libdir' : '<!(pkg-config --libs-only-L protobuf)',
                },
                'link_settings': {
                    'ldflags':                     [ '-Wl,--no-as-needed', ],
                    'libraries': [
                                       '<!@(pkg-config --libs-only-L --libs-only-l protobuf)',
                                       '<!@(./genrpath.sh "<(proto_libdir)")',
                     ],
                 },
            },],
        ],
    },
    'variables': {
        'protoc':               '<!(which protoc)',
        'common_pb_proto':      'common.proto',
        'meta_data_pb_proto':   'meta_data.proto',
        'db_config_pb_proto':   'db_config.proto',
        'svc_config_pb_proto':  'svc_config.proto',
        'diag_pb_proto':        'diag.proto',
        'data_pb_proto':        'data.proto',
        'common_pb_desc':       'lib/common.pb.desc',
        'meta_data_pb_desc':    'lib/meta_data.pb.desc',
        'db_config_pb_desc':    'lib/db_config.pb.desc',
        'svc_config_pb_desc':   'lib/svc_config.pb.desc',
        'diag_pb_desc':         'lib/diag.pb.desc',
        'data_pb_desc':         'lib/data.pb.desc',
        'common_pb_srcs':       [ 'common.pb.h',     'common.pb.cc',     ],
        'meta_data_pb_srcs':    [ 'meta_data.pb.h',  'meta_data.pb.cc',  ],
        'db_config_pb_srcs':    [ 'db_config.pb.h',  'db_config.pb.cc',  ],
        'svc_config_pb_srcs':   [ 'svc_config.pb.h', 'svc_config.pb.cc', ],
        'diag_pb_srcs':         [ 'diag.pb.h',       'diag.pb.cc',       ],
        'data_pb_srcs':         [ 'data.pb.h',       'data.pb.cc',       ],
    },
    'targets': [
        {
            'target_name':       'common_pb_desc',
            'type':              'none',
            'sources':           [ '<(common_pb_proto)', ],
            'actions': [ {
                'action_name':   'protoc_gen_cpp_common',
                'inputs':        [ '<(common_pb_proto)', ],
                'outputs':       [ '<(common_pb_desc)', ],
                'action':        [ '<(protoc)', '--descriptor_set_out=<(common_pb_desc)', '--include_imports', '-I.', '<(common_pb_proto)', ],
            },],
        },
        {
            'target_name':       'meta_data_pb_desc',
            'type':              'none',
            'sources':           [ '<(meta_data_pb_proto)', ],
            'actions': [ {
                'action_name':   'protoc_gen_cpp_meta_data',
                'inputs':        [ '<(meta_data_pb_proto)', '<(common_pb_proto)' ],
                'outputs':       [ '<(meta_data_pb_desc)', ],
                'action':        [ '<(protoc)', '--descriptor_set_out=<(meta_data_pb_desc)', '--include_imports', '-I.', '<(meta_data_pb_proto)', ],
            },],
        },
        {
            'target_name':       'db_config_pb_desc',
            'type':              'none',
            'sources':           [ '<(db_config_pb_proto)', ],
            'actions': [ {
                'action_name':   'protoc_gen_cpp_db_config',
                'inputs':        [ '<(db_config_pb_proto)', '<(common_pb_proto)', '<(meta_data_pb_proto)', ],
                'outputs':       [ '<(db_config_pb_desc)', ],
                'action':        [ '<(protoc)', '--descriptor_set_out=<(db_config_pb_desc)', '--include_imports', '-I.', '<(db_config_pb_proto)', ],
            },],
        },
        {
            'target_name':       'data_pb_desc',
            'type':              'none',
            'sources':           [ '<(data_pb_proto)', ],
            'actions': [ {
                'action_name':   'protoc_gen_cpp_common',
                'inputs':        [ '<(data_pb_proto)', '<(common_pb_proto)', '<(meta_data_pb_proto)', ],
                'outputs':       [ '<(data_pb_desc)', ],
                'action':        [ '<(protoc)', '--descriptor_set_out=<(data_pb_desc)', '--include_imports', '-I.', '<(data_pb_proto)', ],
            },],
        },
        {
            'target_name':       'svc_config_pb_desc',
            'type':              'none',
            'sources':           [ '<(svc_config_pb_proto)', ],
            'actions': [ {
                'action_name':   'protoc_gen_cpp_svc_config',
                'inputs':        [ '<(svc_config_pb_proto)', '<(common_pb_proto)' ],
                'outputs':       [ '<(svc_config_pb_desc)', ],
                'action':        [ '<(protoc)', '--descriptor_set_out=<(svc_config_pb_desc)', '--include_imports', '-I.', '<(svc_config_pb_proto)', ],
            },],
        },
        {
            'target_name':       'diag_pb_desc',
            'type':              'none',
            'sources':           [ '<(diag_pb_proto)', ],
            'actions': [ {
                'action_name':   'protoc_gen_cpp_diag',
                'inputs':        [ '<(diag_pb_proto)', '<(common_pb_proto)' ],
                'outputs':       [ '<(diag_pb_desc)', ],
                'action':        [ '<(protoc)', '--descriptor_set_out=<(diag_pb_desc)', '--include_imports', '-I.', '<(diag_pb_proto)', ],
            },],
        },
    ],
    'conditions': [
        ['"<!(echo $npm_node_execpath)"==""', {
            'targets' : [
                {
                    'conditions': [
                        ['OS=="mac"', {
                            'variables':  { 'proto_root':  '<!(pwd)/..', },
                            'direct_dependent_settings': {
                                'defines':            [ 'USING_PROTO_LIB', 'PROTO_MAC_BUILD', ],
                                'include_dirs':       [ '<(proto_root)/', ],
                                'xcode_settings': {
                                    'OTHER_CFLAGS':     [ '-std=c++11', ],
                                },
                            },
                        },],
                        ['OS=="linux"', {
                            'direct_dependent_settings': {
                                'defines':            [ 'USING_PROTO_LIB', 'PROTO_LINUX_BUILD', ],
                                'include_dirs':       [ '.', ],
                            },
                        },],
                    ],
                    'target_name':       'proto',
                    'type':              'static_library',
                    'sources':           [
                        '<@(common_pb_srcs)',
                        '<@(meta_data_pb_srcs)',
                        '<@(db_config_pb_srcs)',
                        '<@(svc_config_pb_srcs)',
                        '<@(diag_pb_srcs)',
                        '<@(data_pb_srcs)',
                    ],
                    'dependencies':      [
                        'common_pb_cpp',
                        'meta_data_pb_cpp',
                        'db_config_pb_cpp',
                        'svc_config_pb_cpp',
                        'diag_pb_cpp',
                        'data_pb_cpp',
                    ],
                },
                {
                    'target_name':       'common_pb_cpp',
                    'type':              'none',
                    'sources':           [ '<(common_pb_proto)', ],
                    'actions': [{
                        'action_name':   'protoc_gen_cpp_common',
                        'inputs':        [ '<(common_pb_proto)', ],
                        'outputs':       [ '<@(common_pb_srcs)', ],
                        'action':        [ '<(protoc)', '--cpp_out=.', '-I.', '<(common_pb_proto)', ],
                    },],
                },
                {
                    'target_name':       'meta_data_pb_cpp',
                    'type':              'none',
                    'sources':           [ '<(meta_data_pb_proto)', ],
                    'actions': [{
                        'action_name':   'protoc_gen_cpp_meta_data',
                        'inputs':        [ '<(meta_data_pb_proto)', '<@(common_pb_srcs)', ],
                        'outputs':       [ '<@(meta_data_pb_srcs)', ],
                        'action':        [ '<(protoc)', '--cpp_out=.', '-I.', '<(meta_data_pb_proto)', ],
                    },],
                },
                {
                    'target_name':       'db_config_pb_cpp',
                    'type':              'none',
                    'sources':           [ '<(db_config_pb_proto)', ],
                    'actions': [{
                        'action_name':   'protoc_gen_cpp_db_config',
                        'inputs':        [ '<(db_config_pb_proto)', '<@(meta_data_pb_srcs)', '<@(common_pb_srcs)' ],
                        'outputs':       [ '<@(db_config_pb_srcs)', ],
                        'action':        [ '<(protoc)', '--cpp_out=.', '-I.', '<(db_config_pb_proto)', ],
                    },],
                },
                {
                    'target_name':       'data_pb_cpp',
                    'type':              'none',
                    'sources':           [ '<(data_pb_proto)', ],
                    'actions': [{
                        'action_name':   'protoc_gen_cpp_data',
                        'inputs':        [ '<(data_pb_proto)', '<@(meta_data_pb_srcs)', '<@(common_pb_srcs)' ],
                        'outputs':       [ '<@(data_pb_srcs)', ],
                        'action':        [ '<(protoc)', '--cpp_out=.', '-I.', '<(data_pb_proto)', ],
                    },],
                },
                {
                    'target_name':       'svc_config_pb_cpp',
                    'type':              'none',
                    'sources':           [ '<(svc_config_pb_proto)', ],
                    'actions': [{
                        'action_name':   'protoc_gen_cpp_svc_config',
                        'inputs':        [ '<(svc_config_pb_proto)', '<@(common_pb_srcs)' ],
                        'outputs':       [ '<@(svc_config_pb_srcs)', ],
                        'action':        [ '<(protoc)', '--cpp_out=.', '-I.', '<(svc_config_pb_proto)', ],
                    },],
                },
                {
                    'target_name':       'diag_pb_cpp',
                    'type':              'none',
                    'sources':           [ '<(diag_pb_proto)', ],
                    'actions': [{
                        'action_name':   'protoc_gen_cpp_diag',
                        'inputs':        [ '<(diag_pb_proto)', '<@(common_pb_srcs)' ],
                        'outputs':       [ '<@(diag_pb_srcs)', ],
                        'action':        [ '<(protoc)', '--cpp_out=.', '-I.', '<(diag_pb_proto)', ],
                    },],
                },
            ]
        }]
    ]
}
