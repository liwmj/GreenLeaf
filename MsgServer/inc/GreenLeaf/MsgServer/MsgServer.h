/*
 * AntServer.h
 *
 *  Created on: Nov 4, 2014
 *      Author: Mason
 */

#ifndef DEMOSERVER_H
#define DEMOSERVER_H

namespace GreenLeaf {
namespace Server {

class MsgServerImpl;

class MsgServer
{
public:
    explicit MsgServer();
    virtual ~MsgServer();

    void run() const;
    void stop() const;

private:
    MsgServerImpl* _pImpl;

};

} } // GreenLeaf::Server

#endif // DEMOSERVER_H

