//
//  SingletonBLE.h
//  BabyBluetoothAppDemo
//
//  Created by admin on 2019/9/28.
//  Copyright © 2019 admin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    BraceletType_heart = 0,   //血压
    BraceletType_blood,//心率
    BraceletType_stepsNumber, //步数
}BraceletType;

typedef enum : NSUInteger {
    BluetoothStateTyp_PoweredOn = 0,   //蓝牙开启状态
    BluetoothStateTyp_Resetting, //重置
    BluetoothStateTyp_Unsupported, //蓝牙不支持
    BluetoothStateTyp_Unauthorized,//未授权
    BluetoothStateTyp_PoweredOff,//未授权
}BluetoothStateType;


@protocol BleDelegate;
@interface SingletonBLE : NSObject

+(instancetype)shareInstance;


//可保存当前连接的设备，根据需要放在.h或者放在.m中
@property (nonatomic ,strong)CBPeripheral *currentPer;

//当前节点
@property (nonatomic ,strong)CBCharacteristic *characteristic;

@property (nonatomic ,strong)CBCentralManager *myCentralManager;

@property (nonatomic ,assign)BraceletType braceletType; //

@property (nonatomic ,assign)BluetoothStateType bluetoothType; // 设备蓝牙状态


//代理
@property (nonatomic,weak)id <BleDelegate> bleDeagete;

#pragma mark - action of connecting layer - 连接层操作
// 扫描设备
-(void)scanDevice;

//停止扫描
-(void)stopScan;

// 连接设备
- (void)connectPeripheral:(CBPeripheral *)peripheral;

//断开连接设备
-(void)unConnecDevice;


//检索已经连接的外接设备
-(NSArray *)retrieveConnectedPeripherals;


//开始心率
-(void)starDetectionHeartRate;
//停止检测心率
-(void)stopDetectionHeartRate;

//开始检测血压
-(void)starDetectionBloodPressure;

//停止x检测血压
-(void)stopDetectionBloodPressure;

//寻找手环
-(void)searchBracelet;

//步数
-(void)getStepsNumeber;

@end

//代理方法方便外面调用
@protocol BleDelegate <NSObject>

@optional

-(void)BluetoothState:(BluetoothStateType)bluetoothState;

//查找到感兴趣手环的名称
-(void)FoundBraceletName:(CBPeripheral *)Peripheral withAddress:(NSString *)address;

//连接失败
-(void)ConnectFailure;

//连接断开
-(void)ConnectionBroken;

//连接成功，成功之后会自动查询该手环对应的服务，这里不需要做操作，我们只要获取到想要的值就好
-(void)ConnectSuccessful;


//读取检测到的心率，血压以及步数的数值，这里连接之后会返回步数，实时返回，心率以及血压需要手动检测等待结果返回！
-(void)UpdateValueForResult:(NSString *)result with:(BraceletType)braceletType;


@end


NS_ASSUME_NONNULL_END
