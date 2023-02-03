//
//  ContentView.swift
//  war-game-challenge
//
//  Created by Divij on 5/29/21.
//

import SwiftUI

struct ContentView: View {
    @State var cpuScore:Int = 0
    @State var playerScore:Int = 0
    @State var cpuCard:Int = 2
    @State var playerCard:Int = 2

    var body: some View {
        ZStack {
            Image("background")
            VStack {
                Spacer()
                Image("logo")
                Spacer()
                HStack {
                    Spacer()
                    Image("card" + String(playerCard))
                    Spacer()
                    Image("card" + String(cpuCard))
                    Spacer()
                }
                Spacer()
                Button(action: {
                    let playerRand = Int.random(in:2...14)
                    let cpuRand = Int.random(in: 2...14)
                    playerCard = playerRand
                    cpuCard = cpuRand
                    if playerCard>cpuCard {
                        playerScore+=1
                    }
                    else if cpuCard>playerCard {
                        cpuScore+=1
                    }
                }, label: {
                    Image("dealbutton")
                })
                Spacer()
                HStack {
                    Spacer()
                    VStack {
                        Text("Player")
                            .font(.headline)
                            .foregroundColor(Color.white)
                            .padding(.bottom, 10.0)
                            
                        Text(String(playerScore))
                            .font(.largeTitle)
                            .foregroundColor(Color.white)
                            
                                                }
                    Spacer()
                    VStack {
                        Text("CPU")
                            .font(.headline)
                            .foregroundColor(Color.white)
                            .padding(.bottom, 10.0)
                            
                        Text(String(cpuScore))
                            .font(.largeTitle)
                            .foregroundColor(Color.white)
                            
                            
                    }
                    Spacer()
                }
                Spacer()
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
