const ffi = require('ffi');
const express = require('express');
const fs = require('fs');
const child_process = require('child_process');
const bodyParser = require('body-parser');
const cors = require('cors');
const addon = require('./build/Release/addon');

var port = 8120;
var enabled = false;

const app = express();

function Text(text) {
    return new Buffer(text, 'ucs2').toString('binary');
}

var user32 = new ffi.Library('user32', {
    'MessageBoxW': [
        'int32', ['int32', 'string', 'string', 'int32']
    ],
    'EmptyClipboard': ['bool', []],
    'OpenClipboard': ['bool', ['int32']],
    'CloseClipboard': ['bool', []],
    'GetClipboardData': ['string', ['uint']],
    'SetClipboardData': ['string', ['uint', 'string']]
})

// var OK_or_Cancel = user32.MessageBoxW(
//     0, Text('I am Node.JS!'), Text('Hello, World!'), 1
//  );
user32.OpenClipboard(0);
var data = user32.GetClipboardData(1);
console.log(data);
var val = user32.CloseClipboard();
console.log(val);
// user32.EmptyClipboard();
app.use(bodyParser.json());
app.use(cors());
app.use(bodyParser.urlencoded({
    extended: true
}));

var router = express.Router();

router.route('/newOTP').post(function (req, res) {
    res.json({
        hello: 'hey guys'
    });
    if (enabled) {
        addon.writeToClipboard(req.body.message);
    } else {
        try {
            var value = "\n" + req.body.message
            fs.appendFileSync('otp.txt',value);

            child_process.exec('open.bat', (err, stdout, stderr) => {
                if (err) {
                    console.error(err);
                    return;
                }
                console.log(stdout);
            });
        } catch (e) {
            if (e) {
                console.log(e);
            }
        }
    }
});

app.use('/api', router);

app.listen(port, function () {
    console.log("listening at port:" + port);
})