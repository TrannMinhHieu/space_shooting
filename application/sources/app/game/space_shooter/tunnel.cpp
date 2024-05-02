// #include "tunnel.h"

// Tunnel myTunnel;

// int safe_distance = 40;
// int coeff_y = 0;

// void tunnel_init()
// {
//     APP_DBG_SIG("Tunnel init\n");
//     myTunnel.visible = WHITE;
//     myTunnel.x = 0;
//     myTunnel.y = 0;
// }
// void tunnel_generate_y_coordinate()
// {
// }

// void tunnel_advance()
// {
//     APP_DBG_SIG("Tunnel advance\n");
//     if (myTunnel.y + safe_distance > LCD_HEIGHT)
//     {
//         myTunnel.y = (rand() % 6) * 10;
//         coeff_y = myTunnel.y + safe_distance + 5;
//     }

//     if (myTunnel.x + TUNNEL_WIDTH < LCD_WIDTH)
//     {
//         myTunnel.x = LCD_WIDTH;
//         myTunnel.x -= myShip.fly_speed;
//     }
// }

// void tunnel_handler(ak_msg_t *msg)
// {
//     switch (msg->sig)
//     {
//     case TUNNEL_INIT_SIG:
//         tunnel_init();
//         break;
//     case TUNNEL_GENERATE_SIG:
//         tunnel_advance();
//         break;
//     default:
//         break;
//     }
// }

// // //screen size 640 x 480
// // safeViewDistance = 700; //How far can the player see
// // playerX;
// // averageDist = 100 // averageDistanceBet
// // lastX = - 2.5 * averageDist //the further point in the tunnel
// // tunnelHeight = 300 // space between ceiling to floor

// // while(lastX < playerX + safeViewDistance)
// // {
// //     lastX += (0.5 + Math.random()) * averageDist;
// //     points.push(new Point(lastX, Math.random());
// // }

// // to draw the ceiling and floor use bezier:
// // lastDrawnPoint = 1;
// // function drawPoints(yOffset, yCoeff)
// // {
// //     while(lastDrawnPoint < points.length)
// //     {
// //         i = lastDrawnPoint;
// //         startPoint = average(points[i-1], points[i]);
// //         controlPoint = points[i];
// //         endPoint = average(points[i],points[i+1]);

// //         startPoint.y *= yCoeff;
// //         startPoint.y += yOffset;
// //         //repeat for control and end

// //         drawBezier(startPoint, controlPoint, endPoint);
// //     }
// // }