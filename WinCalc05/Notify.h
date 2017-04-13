#if !defined (NOTIFY_H)
#define NOTIFY_H
// Bartosz Milewski (c) 2000
#include <windows.h>

const UINT UM_MEMCLEAR = WM_USER;

class NotificationSink
{
public:
	virtual void AddItem (int id) = 0;
	virtual void UpdateItem (int id) = 0;
};

#endif
