#ifndef EVENT_H
#define EVENT_H

namespace Xeebo {

enum class Event {
  /**
   * Xeebo::Event::Frame_Update is the event triggered on a frame update
   * if nothing else happens that frame.
   */
  Frame_Refresh = 0
};

} // namespace Xeebo

#endif // EVENT_H
