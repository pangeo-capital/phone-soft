#include "SipiosWrap.h"
#include "common\mapRefObj.h"

refs_objs<si_endpoint_t, Sipios_Endpoint*> objs;

//***************
// Endpoint
//***************
void Endpoint_onTransportState(si_endpoint_t e, int state) {
  objs.getObj(e)->onTransportState(state);
}

void Endpoint_onPreviewVideo(si_endpoint_t e, void* window) {
  objs.getObj(e)->onPreviewVideo(window);
}

void Endpoint_onStop(si_endpoint_t e) {
  objs.getObj(e)->onStop();
}


Sipios_Endpoint::Sipios_Endpoint() {
  si_ep_set_cb(Endpoint_onTransportState, Endpoint_onPreviewVideo, Endpoint_onStop);
  objs.setObj(si_ep_create(), this);
}

Sipios_Endpoint::~Sipios_Endpoint() {
  si_ep_drop(objs.getRef(this));
  objs.removeObj(this);
}

void Sipios_Endpoint::hangup_all() {
  si_ep_hangup_all(objs.getRef(this));
}

void Sipios_Endpoint::setSndDev(const std::string& dev) {
  si_ep_drop(objs.getRef(this));
}

void Sipios_Endpoint::startPreview(int dev, int x, int y, int w, int h) {
}

void Sipios_Endpoint::stopPreview(int dev) {

}
/**************/

