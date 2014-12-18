var fs       = require('fs');
var protobuf = require('node-protobuf');

var virtdb = {};

virtdb.data =  new protobuf((fs.readFileSync(__dirname + '/data.pb.desc')));
virtdb.db_config =  new protobuf((fs.readFileSync(__dirname + '/db_config.pb.desc')));
virtdb.diag =  new protobuf((fs.readFileSync(__dirname + '/diag.pb.desc')));
virtdb.meta_data =  new protobuf((fs.readFileSync(__dirname + '/meta_data.pb.desc')));
virtdb.service_config =  new protobuf((fs.readFileSync(__dirname + '/svc_config.pb.desc')));

module.exports = virtdb;
