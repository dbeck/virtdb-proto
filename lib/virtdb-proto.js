var fs       = require('fs');
var protobuf = require('node-protobuf');

(function () {

    var virtdb = {};

    virtdb.data =  new protobuf((fs.readFileSync('data.pb.desc')));
    virtdb.db_config =  new protobuf((fs.readFileSync('db_config.pb.desc')));
    virtdb.diag =  new protobuf((fs.readFileSync('diag.pb.desc')));
    virtdb.meta_data =  new protobuf((fs.readFileSync('meta_data.pb.desc')));
    virtdb.service_config =  new protobuf((fs.readFileSync('svc_config.pb.desc')));

    module.exports = virtdb;
)
