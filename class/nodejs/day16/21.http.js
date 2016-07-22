/**
 * Created by KICT-22 on 2016-07-19.
 */

const http = require('http');
const util = require('util');
const os = require('os');
const UrlParser = require('url');

let solution;
let bSolved = true;
let AdminPasswd = "abc";
let Winner_name="";

let http_server = http.createServer(
    (req,res)=> {
        console.log(req.url);

        var url_obj = UrlParser.parse(req.url,true);
        console.log(url_obj);

        let header = {
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'GET',
            'Access-Control-Allow-Max-Age': '1000'
        };
        header['Content-Type'] = 'text/plain'; //text ***
        res.writeHead(200,header);

        switch(url_obj.pathname) {
            case '/sum':
                let c = parseInt(url_obj.query.a) +
                    parseInt(url_obj.query.b);
                res.end("result : " +c);


                break;
            //http://localhost:8080/game-try?value=84&name=안철수
            case '/game-try':
                if(bSolved ==false) {
                    if(url_obj.query.value == solution) {
                        Winner_name = url_obj.query.name;
                        bSolved = true;
                        res.end("bingo");

                    }
                    else if(url_obj.query.value > solution) {
                        res.end("high")
                    }
                    else if(url_obj.query.value < solution) {
                        res.end("low");
                    }
                }
                else {
                    res.end(solution +
                        "game over, Winner is" +
                    Winner_name);

                }
                break;
            case '/start-game':
                if(url_obj.query.passwd == AdminPasswd) {
                    solution = Math.round(Math.random()*100);
                    bSolved =false;
                    Winner_name = "";
                    res.end("start ok : " + solution)
                }
                else {
                    res.end("wrong passwd");
                }
                break;
            default:
                res.end("it is bingo api server");
                break;
        }

    }

);
http_server.listen(8080);