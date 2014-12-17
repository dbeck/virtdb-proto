fs          = require 'fs'
protobuf    = require 'node-protobuf'

(function () {

    var virtdb = {};

    virtdb.data =  new protobuf('data.pb.desc'));
    virtdb.db_config =  new protobuf('db_config.pb.desc'));
    virtdb.diag =  new protobuf('diag.pb.desc'));
    virtdb.meta_data =  new protobuf('meta_data.pb.desc'));
    virtdb.service_config =  new protobuf('svc_config.pb.desc'));

    module.exports = virtdb;
)
