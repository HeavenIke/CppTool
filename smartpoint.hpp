#ifndef ARC_SMART_POINT_HPP
#define ARC_SMART_POINT_HPP
namespace cpptool {

class counter
{
    template<class T> friend class SmartPoint;
    counter(int use) : use_(use) {}
    ~counter(){}
    int use_;
};

template<class T>
class SmartPoint
{
public:
    SmartPoint() : pObj_(NULL), pCounter_(NULL) {
    }

    SmartPoint(T* ptr)
        :pObj_(ptr),
        pCounter_(new counter(1))
    {
    }

    SmartPoint(SmartPoint<T>& val)
    {
	if (val.pObj_ != NULL && val.pCounter_ != NULL) {
        	pObj_ = val.pObj_;
        	pCounter_ = val.pCounter_;
        	pCounter_->use_++;
	} else {
		pCounter_ = NULL;
		pObj_ = NULL;
	}

    }

    ~SmartPoint()
    {
        if (pObj_ != NULL && pCounter_ != NULL) {
            pCounter_->use_--;
            if (pCounter_->use_ == 0)
            {
                delete pObj_;
                delete pCounter_;
            }
        }
    }

    bool operator == (SmartPoint<T> val)
    {
       return (val.pObj_ == pObj_ && val.pCounter_ == pCounter_);
    }

    SmartPoint<T>& operator = (SmartPoint<T>& val)
    {
        if (this != &val) {
            if (pCounter_ && (--pCounter_->use_) == 0) {
                delete pCounter_;
                delete pObj_;
            }
            val.pCounter_->use_++;

            pCounter_ = val.pCounter_;
            pObj_= val.pObj_;
        } 

        return *this;

    }

    T& operator * ()
    {
        return *pObj_;
    }

    T* operator -> ()
    {
        return pObj_;
    }

    bool isNULL() const
    {
        return (pObj_ == NULL  && pCounter_ == NULL);
    }

private:
    T* pObj_;
    counter* pCounter_; 
};


} // namespace cpptool

#endif
