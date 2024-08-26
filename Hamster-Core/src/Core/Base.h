    #pragma once

#define BIND_EVENT_TYPE(type) static EventType GetStaticEventType() {return EventType::type;} virtual EventType GetEventType() const override {return GetStaticEventType();} virtual std::string GetEventName() const override {return #type;}
#define FORWARD_CALLBACK_FUNCTION(func, eventClass) [this](Event& e) {this->func(dynamic_cast<eventClass&>(e));}

#define XGuizmoID 16777214
#define YGuizmoID 16777213