var log;

var param_x_pos = 30;
var param_y_pos = 20;
var param_offset = 20;
var param_x_offset1 = 135;
var which_point = 0;

function preload() 
{
    //This is currently a placeholder for the JSON file
    log = 
    {
        points: 
        [
            {   "id" : 1111,
                "time" : "16:20:00 20/4/2020",
                "gps_lat" : 34.191996, 
                "gps_long" : -118.337113,
                "rssi" : -69
            },

            {   "id" : 1111,
                "time" : "16:20:02 20/4/2020",
                "gps_lat" : 34.191966, 
                "gps_long" : -118.335936,
                "rssi" : -42
            },

            {   "id" : 1111,
                "time" : "16:20:04 20/4/2020",
                "gps_lat" : 34.192265, 
                "gps_long" : -118.335843,
                "rssi" : -33
            },

            {   "id" : 1111,
                "time" : "16:20:06 20/4/2020",
                "gps_lat" : 34.192579, 
                "gps_long" : -118.335839,
                "rssi" : -25
            }
        ]
    }
}

function setup() 
{
    createCanvas(1000, 600);
}

function draw() 
{
    background(0);

    textFont('Rubik');
    display_datapoint_params();
}

//Right and left arrows will allow us to page through our data points
function keyPressed()
{
    if(keyCode == RIGHT_ARROW && which_point < 3) {which_point ++;}
    else if (keyCode == LEFT_ARROW && which_point > 0) {which_point --;}
    return false;
}

function display_datapoint_params()
{
    fill(50);
    rect(param_x_pos-(param_offset/2.0), param_y_pos, 265, 155);
    
    fill(255);
    text("DATAPOINT NUMBER", param_x_pos, param_y_pos + (param_offset * 1));
    text("DEVICE ID", param_x_pos, param_y_pos + (param_offset * 3));
    text("TIME", param_x_pos, param_y_pos + (param_offset * 4));
    text("GPS LATITUDE", param_x_pos, param_y_pos + (param_offset * 5));
    text("GPS LONGITUDE", param_x_pos, param_y_pos + (param_offset * 6));
    text("RSSI", param_x_pos, param_y_pos + (param_offset * 7));

    text(which_point, param_x_pos + param_x_offset1, param_y_pos + (param_offset * 1));
    text(log.points[which_point].id, param_x_pos + param_x_offset1, param_y_pos + (param_offset * 3));
    text(log.points[which_point].time, param_x_pos + param_x_offset1, param_y_pos + (param_offset * 4));
    text(log.points[which_point].gps_lat, param_x_pos + param_x_offset1, param_y_pos + (param_offset * 5));
    text(log.points[which_point].gps_long, param_x_pos + param_x_offset1, param_y_pos + (param_offset * 6));
    text(log.points[which_point].rssi, param_x_pos + param_x_offset1, param_y_pos + (param_offset * 7));
}